import shutil
import os

logging = None
verbose = False


def init(loggingFromRemote):
    global logging
    logging = loggingFromRemote


class _Function:
    # Wrap copy file to prevent change copy method in future
    #
    def copy(sourceFilePath, targetFilePath):
        # Create folder if not exist
        targetFilePath.parent.mkdir(parents=True, exist_ok=True)

        # Copy
        try:
            shutil.copyfile(sourceFilePath, targetFilePath)
        except IOError as e:
            print(e)
            breakpoint()
            logging.error(e)

    # Check condition first, if true then run action
    def compare(sourceFilePath, targetFilePath, action=None):
        # Only check if target file already exist to avoid error
        if targetFilePath.is_file():
            sourceFileTime = os.path.getmtime(sourceFilePath)
            targetFileTime = os.path.getmtime(targetFilePath)

            if sourceFileTime > targetFileTime:
                action(sourceFilePath, targetFilePath)
        # Target file not exist copy directly
        else:
            action(sourceFilePath, targetFilePath)


def copy_if_newer(sourceFilePath, targetFilePath):
    _Function.compare(sourceFilePath, targetFilePath, _Function.copy)

# Print only if verbose


def verbose_print(message):
    if verbose:
        print(message)
