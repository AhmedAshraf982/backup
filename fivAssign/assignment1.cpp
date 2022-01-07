#include<iostream>
#include<vector>  //vector included to compare the two lists without sorting them to make the solution optimal
using namespace std;
class Book{  //book class to hold the book details
	string title;
	string author;
	string isbn;
	Book* next;
	public:
	    Book(){  //default constructor
	    	next = NULL;
		}
		Book(string title, string author, string isbn){  //paramterized constructor that sets every attribute of a particular book
			this->title = title;
			this->author = author;
			this->isbn = isbn;
			next = NULL;
		}
		void setNext(Book* next){  //to set the next pointer to point a new book
			this->next = next;
		}
		string getTitle(){  //returns title of the book
			return title;
		}
		string getAuthor(){  //returns the author of the book
			return author;
		}
		string getIsbn(){  //returns the isbn of the book
			return isbn;
		}
		Book* getNext(){  //returns the next pointer of a book
			return next;
		}
		bool operator==(Book& book){  //used to compare to books as if they are equal or not, for that we compare the title, author and isbn of two books
			if(this->getTitle() == book.getTitle() && this->getAuthor() == book.getAuthor() && this->getIsbn() == book.getIsbn()){
				return true;
			}
			return false;
		}
};
class List{   //list class to hold books in a singly linked list format
	Book* head;
	public:
		List(){
			head = NULL;   //setting the head as null as emptiness of  the list
		}
		void setHead(Book* head){  //used to set the head pointer to point a book as a starting point of the list
			this->head = head;
		}
		Book* getHead(){  //to get the head pointer
			return head;
		}
		bool isEmpty(){  //checks if the list is empty by the same concept as described in the default constructor
			if(head == NULL)
			   return true;
			else
			   return false;
		}
//		void insert(Book book){   //utility function, not required in solution
//			if(isEmpty()){
//			    head = new Book(book.getTitle(), book.getAuthor(), book.getIsbn());	
//			    return;
//			}
//			Book* node;
//			for(node = head; node->getNext() != NULL; node = node->getNext()){}
//			Book* newNode = new Book(book.getTitle(), book.getAuthor(), book.getIsbn());
//			node->setNext(newNode);
//		}
//		void traverse(){   //utility function, not required in solution
//			for(Book* node = head; node != NULL; node = node->getNext()){
//				cout << node->getTitle() << endl;
//			}
//		}
		int size(){  //to get the size i.e. the number of books in a list
			int count = 0;
			Book* node;
			for(node = head; node != NULL; node = node->getNext()){
				count++;
			}
			return count;
		}
		vector<Book> getBooksToVector(){   //stores all the books from the list to a vector for simplification of comparison
			vector<Book> books;
			Book* node;
			for(node = head; node != NULL; node = node->getNext()){
				books.push_back(*node);
			}
			return books;
		}
};
bool isInList(List& list, Book& book){   //checks if a book is in the given list
	if(list.isEmpty()){
		return false;
	}
	Book* head = list.getHead();
	Book* node;
	for(node = head; node != NULL; node = node->getNext()){
		if(*node == book){
			return true;
		}
	}
	return false;
}
void addBook(List& list, Book& book){  //adds a new book to the list
	Book* head = list.getHead();
	if(list.isEmpty()){  //first we check if the list is empty, if yes, so the given book is obviously not in the list.
		head = new Book(book.getTitle(), book.getAuthor(), book.getIsbn());
		list.setHead(head);
		return;
	}
	if(!isInList(list, book)){   //if it is already in the list, we do not add it, else we do
		Book* node;
	    for(node = head; node->getNext() != NULL; node = node->getNext()){}
	    Book* newNode = new Book(book.getTitle(), book.getAuthor(), book.getIsbn());
	    node->setNext(newNode);
	}
}
bool compareLists(List& list1, List& list2){  //compares two given lists by transforming the list to a vector, and then checking
	if(list1.size() != list2.size()){
		return false;
	}
	vector<Book> books1 = list1.getBooksToVector();
	vector<Book> books2 = list2.getBooksToVector();
	for(int x = 0; x < books1.size(); x++){
		bool flag = true;
		for(int y = 0; y < books2.size(); y++){
			if(books1[x] == books2[y]){
				flag = false;
				break;
			}
		}
		if(flag){
			return false;
		}
	}
	return true;
}
int main(){  //driving code
	List list;
	//adding books
	
	Book* book = new Book("Sherlock Holmes", "Arhtur", "2345678901");
	addBook(list, *book);
	book = new Book("Rich dad poor dad", "Robert Kiyosaki", "9234567897");
	addBook(list, *book);
	book = new Book("Alchemist", "Paulo Coelho", "1234567890");
	addBook(list, *book);
    Book* checkABook = new Book("Sherlock Holmes", "Arhtur", "2345678901");
    //checling if the above book exists in the list
    if(isInList(list, *checkABook) ){
    	cout << "The book \'" << checkABook->getTitle() << "\' exists in the list." << endl;
	}else{
		cout << "The book \'" << checkABook->getTitle() << "\' does not exist in the list." << endl;
	}
	//making another list for comparison
    List list2;
    book = new Book("Sherlock Holmes", "Arhtur", "2345678901");
	addBook(list2, *book);
	book = new Book("Alchemist", "Paulo Coelho", "1234567890");
	addBook(list2, *book);
	book = new Book("Rich dad poor dad", "Robert Kiyosaki", "9234567897");
	addBook(list2, *book);
	
    //comparing list and list2
	if(compareLists(list, list2)){
		cout << "The two books lists are equal!";
	}else{
		cout << "The two books lists are not equal!";
	}
}
