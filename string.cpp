#include <thread>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

int times = 0;
struct Word
{
  char * data;
  int count;

  Word(){
  	data = new char[100];
  }
  Word ( char * data_ ) :
    data( ::strdup(data_) )
  {}
  Word(struct Word& word){
  	this->count = word.count;
  	strcpy(this->data, word.data);
  }
  Word* operator=(struct Word& word){
  	this->count = word.count;
  	strcpy(this->data, word.data);
  	return this;
  }
};

std::vector<Word*> s_wordsArray;
Word s_word;
int s_totalFound;


// Worker thread: consume words passed from the main thread and insert them
// in the 'word list' (s_wordsArray), while removing duplicates. Terminate when
// the word 'end' is encountered.
void workerThread ()
{
  bool endEncountered = false;
  bool found = false;
  
  while (!endEncountered)
  {
    if (s_word.data[0]) // Do we have a new word?
    {
      Word w;
	  w = s_word; // Copy the word
      s_word.data[0] = 0; // Inform the producer that we consumed the word
      endEncountered = (std::strcmp( w.data, "end" ) == 0);
     // free(s_word.data);
      if (!endEncountered)
      {
        // Do not insert duplicate words
        if(times > 0){
        	s_wordsArray.push_back(&w);
        	std::printf("word pushed: %s  %s", s_wordsArray[0]->data, w.data);
        }
        times++;
      }
    }
  }
};

// Read input words from STDIN and pass them to the worker thread for
// inclusion in the word list.
// Terminate when the word 'end' has been entered.
//
static void readInputWords ()
{
  bool endEncountered = false;
  
  std::thread * worker = new std::thread( workerThread );
  char * linebuf = new char[32];
  while (!endEncountered)
  {
  	fflush(stdin);
    std::gets(linebuf);
    
    endEncountered = (std::strcmp( linebuf, "end" ) == 0);
    // Pass the word to the worker thread
    std::strcpy( s_word.data, linebuf );
    while (s_word.data[0]); // Wait for the worker thread to consume it
  }
  
  worker->join(); // Wait for the worker to terminate
}

// Repeatedly ask the user for a word and check whether it was present in the word list
// Terminate on EOF
//
static void lookupWords ()
{
  bool found;
  char * linebuf = new char[32];
    
  for(;;)
  {
    std::printf( "\nEnter a word for lookup:" );
    if (std::scanf( "%s", linebuf ) == EOF)
      return;

    // Initialize the word to search for
    Word * w = new Word();
    std::strcpy( w->data, linebuf );

    // Search for the word
    unsigned i;
    if(s_wordsArray.size()){
    	for ( i = 0; i < s_wordsArray.size(); ++i )
    {
      if (std::strcmp( s_wordsArray[i]->data, w->data ) == 0)
      {
        found = true;
        break;
      }
    }
	}

    if (found)
    {
      std::printf( "SUCCESS: '%s' was present %d times in the initial word list\n",
                   s_wordsArray[i]->data, s_wordsArray[i]->count );
      ++s_totalFound;
    }
    else
      std::printf( "'%s' was NOT found in the initial word list\n", w->data );
  }
}

int main ()
{
  try
  {
    readInputWords();
    // Sort the words alphabetically
   // std::sort( s_wordsArray.begin(), s_wordsArray.end() );
    // Print the word list
    std::printf( "\n=== Word list:\n" );
    if(s_wordsArray.size()){
    	for (int x = 0; x < s_wordsArray.size(); x++){
    		std::printf( "%s %d\n", s_wordsArray[x]->data, s_wordsArray[x]->count);
		}
	}
    lookupWords();

    printf( "\n=== Total words found: %d\n", s_totalFound );
  }
  catch (std::exception & e)
  {
    std::printf( "error %s\n", e.what() );
  }
  
  return 0;
}
