# Example config file format
# $configFile = @(($prefetchFolderArray | ConvertTo-Json), ($excludeFolderArray | ConvertTo-Json))
# Then wrap the json with named key and values.
# It looks like {"var1":[],"var2":[]]
# after loaded and decoded, 0 would be prefetch folder, 1 would be exclude folder
$configFile = (Get-Content ".\Prefetch.json" -Raw) | ConvertFrom-Json
$prefetchFolderArray = $configFile.prefetchFolderArray
$excludeFolderArray = $configFile.excludeFolderArray

# The actual method to read a file from disk
# This method is allowed to run failed and ignore any error
# So there is no need to place a try block while method call
function ReadMyFile {
    param (
        $FilePath
    )
    
    try {
        # method 4 fastest but
        # have question about is the file indeed loaded into ram?
        #$File = [system.io.file]::OpenRead($FilePath)
        #$File.Close()
        
        # method 2 relatively fast but it will make sure the file is loaded
        $myReadedBytes = [System.IO.File]::ReadAllBytes("$myFileFullPath")
        
        # method 3 slow
        #Get-ChildItem $myFileFullPath | Get-Content | Out-Null
    
        # method 1 slow
        #$myReadedTexts = [System.IO.File]::ReadAllText("$myFileFullPath")
    }
    # This method is allowed to run failed and ignore any error
    catch {
    }
}

# The iterate based path processing method
# There is two calling option
#   If a folder is required to prefetch,
#     use Itr_Prefetch -Folder "C:\Demo" or Itr_Prefetch "C:\Demo"
#   Or if only one file is required to prefetch,
#     use Itr_Prefetch -File "C:\Demo.img"
#   To notice once the two option is used at the same time,
#   Only file mode would be used and other information is ignored.
function Itr_Prefetch {
    # Folder mode or file mode
    param($Folder, $File = $False)
	
    # If working on folder mode
    if ($File -eq $False) {
        # Loop through files under current(input) folder
        $myFileSet = Get-ChildItem -LiteralPath $Folder -File
        foreach ($myFileToPrefetch in $myFileSet) {
            # Export file name with path
            $myFileFullPath = $myFileToPrefetch.FullName
            # Prefetch it
            # ITRRRRRRRRRRRRR!!!
            Itr_Prefetch -File $myFileFullPath
        }
        
        # After all files is loaded, keep running for subfolders

        # Loop through folders under current(input) folder
        $myFolderSet = Get-ChildItem -LiteralPath $Folder -Directory
        foreach ($myFolderToPrefetch in $myFolderSet) {
            # Export folder name with path
            $myFolderFullPath = $myFolderToPrefetch.FullName

            # Check if exclude
            if ($excludeFolderArray -contains $myFolderFullPath) {
                # Exclude this folder by skip this foreach step
                continue
            }

            # Prefetch it
            # ITRRRRRRRRRRRRR!!!
            Itr_Prefetch $myFolderFullPath
        }
    }
    else {
        # The method ReadMyFile is designed for "Always success"
        # so there is no try block
        ReadMyFile -FilePath $File
    }
}

Write-Output "Prefetching..."

foreach ($rootFolderToPrefetch in $prefetchFolderArray) {
    Itr_Prefetch -Folder $rootFolderToPrefetch
}
exit