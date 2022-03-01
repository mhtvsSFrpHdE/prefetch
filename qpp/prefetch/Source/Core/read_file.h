// Static class
class ReadFile
{
public:
    // Start read file
    static void start();

    // Iterated function counter
    // Can confirm if there is a dead loop
    static int count_start_scanFolder;

private:
    // Disallow creating an instance of this object
    ReadFile() {}
};
