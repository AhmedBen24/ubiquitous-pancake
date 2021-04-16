/* This is a sample solution for Porject5 that you
   can use for your project 6. The code can perform
   most of commands except doResize() and doFile().
   There are no desructor or functions to remove nodes
   either.   */

#include "island.h"

class ArchipelagoExpedition
{
private:
    // Create the Data Members for the Archipelago Network here
    Island *expedition;
    int numIslands;
    FileList file;
    myQueue islandQueue;
    myStack pathList;

    // Add file data member here
    // you can either use a linked list of strings
    // or a dynamic array of strings

public:

    // Use a constructor to initialize the Data Members for your expedition
    ArchipelagoExpedition()
    {
        numIslands = 10;
        expedition = new Island[numIslands]();

    }

    void depthFirstSearchHelper(int x, int y){
        for(int i = 0; i < numIslands; i++){
            expedition[i].setVisited(false);
        }

        if(dfs(x,y) == true)
            printf("You can get from island %d to island %d in one or more ferry rides\n", x, y);
        else
            printf("You can NOT get from island %d to island %d in one or more ferry rides\n", x, y);
    }


    bool dfs(int x, int y){
        for(int i = 0; i < expedition[x-1].getAdjacent()->getListLength(); i++){
            int island = expedition[x-1].getAdjacent()->getNthElem(i);
            if(island == y)
                return true;

            if(!expedition[island - 1].getVisited()){
                expedition[x-1].setVisited(true);

                if (dfs(island, y))
                    return true;
            }
        }
        return false;
    }

    bool bfs(int b, myQueue &IslandQ)
    {

        while (!IslandQ.isTheListEmpty()) {
            int a = IslandQ.peak();
            IslandQ.dequeue();
            for(int i = 0; i < expedition[a-1].getAdjacent()->getListLength(); i++) {
                int c = expedition[a-1].getAdjacent()->getNthElem(i);
                if(!expedition[c-1].getVisited()){
                    expedition[c-1].setVisited(true);
                    expedition[c-1].setPreviousLocation(a);

                    if (c == b)
                        return true;
                    IslandQ.enqueue(c);
                }
            }
        }
        return false;
    }

    myStack breadthFirstSearch(int x, int y)
    {
        // Mark all islands as unvisited:
        myStack adjPath;
        myQueue QueForIsland;
        for(int i = 0; i < numIslands; i++){
            expedition[i].setVisited(false);
            expedition[i].setPreviousLocation(-1);
        }

        QueForIsland.enqueue(x);     // Add x to the end


        if (!bfs(y,QueForIsland)) {
            cout << "You can NOT get from island " << x << " to island " << y << endl;
            return adjPath;
        } else{
            // When a path exists:
            cout << "You can get from island " << x << " to island " << y <<  endl;
            // adjPath.removeList();
            int currentIsland = y;
            adjPath.push(currentIsland);

            do {
                currentIsland = expedition[currentIsland-1].getPreviousLocation();
                adjPath.push(currentIsland);
            } while (currentIsland != x);
            // adjPath.printList();
            return adjPath;

        }

      
    }


    void processCommandLoop (FILE* inFile)
    {
        char  buffer[300];
        char* input;

        input = fgets ( buffer, 300, inFile );   // get a line of input

        while (input != NULL)
        {
            // process each line of input using the strtok functions
            char* command;
            command = strtok (input , " \r\n\t");

            printf ("*%s*\n", command);

            if ( command == NULL )
                printf ("Blank Line\n");

            else if ( strcmp (command, "q") == 0)
                exit(1);

            else if ( strcmp (command, "?") == 0)
                showCommands();

            else if ( strcmp (command, "t") == 0)
                doTravel();

            else if ( strcmp (command, "s") == 0)
                doShortestPath();
            

            else if ( strcmp (command, "r") == 0)
                doResize();

            else if ( strcmp (command, "i") == 0)
                doInsert();

            else if ( strcmp (command, "d") == 0)
                doDelete();

            else if ( strcmp (command, "l") == 0)
                doList();

            else if ( strcmp (command, "f") == 0)
                doFile();

            else if ( strcmp (command, "#") == 0)
                ;

            else
                printf ("Command is not known: %s\n", command);

            input = fgets ( buffer, 300, inFile );   // get the next line of input

        }
    }

    void showCommands()
    {
        printf ("The commands for this project are:\n");
        printf ("  q \n");
        printf ("  ? \n");
        printf ("  # \n");
        printf ("  s <int1> <int2> \n");
        printf ("  t <int1> <int2> \n");
        printf ("  r <int> \n");
        printf ("  i <int1> <int2> \n");
        printf ("  d <int1> <int2> \n");
        printf ("  l \n");
        printf ("  f <filename> \n");
    }

    void doShortestPath(){
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok (NULL, " \n\t");
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val1 = atoi ( next );
        if ( val1 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok (NULL, " \n\t");

        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val2 = atoi ( next );
        if ( val2 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }
      // check for greater than numIslands
      if ( (val2 > numIslands) || (val1 > numIslands) )
        {
            printf ("Invalid value for island\n");
            return;
        }
        printf ("Performing the shortest path Command from %d to %d\n",
                val1, val2);
                
       myStack path = breadthFirstSearch(val1, val2);

       if (!path.isTheListEmpty()) {
        cout << "shortest path from " << val1 << " to " << val2 << ": " ;
        path.printList2();
        } 
        cout << endl;
    }

    void doTravel()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok (NULL, " \r\n\t");


        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val1 = atoi ( next );
        if ( val1 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok (NULL, " \r\n\t");
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val2 = atoi ( next );
        if ( val2 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }


        printf ("Performing the Travel Command from %d to %d\n",
                val1, val2);
        depthFirstSearchHelper(val1, val2);
    }

    void doResize()
    {
        int val1 = 0;
        // get an integer value from the input
        char* next = strtok (NULL, " \r\n\t");
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
      
        delete[] expedition;
        numIslands = val1;
        expedition = new Island[numIslands];

        for(int i = 0; i < val1; i++){
           expedition[i].setNumber(i+1);
           expedition[i].setVisited(false);
       }
        printf ("Performing the Resize Command with %d\n", val1 );

    }

    void doInsert()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok (NULL, " \r\n\t");
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val1 = atoi ( next );
        if ( val1 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok (NULL, " \r\n\t");
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val2 = atoi ( next );
        if ( val2 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }

        if(val1 <= numIslands && val2 <= numIslands){
            printf ("Performing the Insert Command for %d\n", val1 );
            expedition[val1-1].getAdjacent()->insert(val2);
            expedition[val2-1].setPreviousLocation(val1);


            }
        else
            printf("Invalid value for island\n");
    }

    void doDelete()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok (NULL, " \r\n\t");
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val1 = atoi ( next );
        if ( val1 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok (NULL, " \r\n\t");
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val2 = atoi ( next );
        if ( val2 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }
        if ( (val2 > numIslands) || (val1 > numIslands) )
        {
            printf ("Invalid value for island\n");
            return;
        }
        printf ("Performing the Delete Command for %d\n", val1 );
        
        expedition[val1-1].getAdjacent()->remove(val2);
    }

    void doList()
    {
        printf ("Displaying the adjacency list:\n" );
        for(int i = 0; i < numIslands; i++) {
          if(expedition[i].getSize() == 0){
            printf("%d -->", i+1);
            printf("\n");
          } else{
            printf("%d -->   ", i+1);
            expedition[i].getAdjacent()->printList();
            printf("\n");
          }
            
        }
    }

    void doFile()
    {
        // get a filename from the input
        char* fname = strtok (NULL, " \r\n\t");
        if ( fname == NULL )
        {
            printf ("Filename expected\n");
            return;
        }

        printf ("Performing the File command with file: %s\n", fname);

        // next steps:  (if any step fails: print an error message and return )
        //  1. verify the file name is not currently in use
        //  2. open the file using fopen creating a new instance of FILE*
        //  add file to dynamic array
        //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
        //  4. close the file when processCommandLoop() returns
        //  5. Remove the file name from the array

      if (file.isValid(fname)) {
        cout << "File is already in use" << endl;
        return;
      }
        FILE* fileName;
        fileName = fopen(fname, "r");

        if(fileName == NULL){
            cout << "File is already in use" << endl;
            return;
        }
        file.addTheFile(fname);

        processCommandLoop(fileName);

        fclose(fileName);
        file.deleteFile(fname);


    }
};

int main (int argc, char** argv)
{
    // set up the variable inFile to read from standard input
    FILE* inFile = stdin;

    // set up the data needed for the island adjcency list
    ArchipelagoExpedition islandData;

    // call the method that reads and parses the input
    islandData.showCommands();
    printf ("\nEnter commands at blank line\n");
    printf ("    (No prompts are given because of f command)\n");
    islandData.processCommandLoop (inFile);

    printf ("Goodbye\n");

    return 1;
}