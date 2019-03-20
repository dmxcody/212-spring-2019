#define uint unsigned int

class MyString {
	private:
		char* string;

	public:
		// Constructor and Destructor
		MyString();
		MyString(const char*);
		~MyString();

		// Other Functions.
		uint len();

		void set(int, char);
		const char get(int);

		char* c_str();

		void reverse();

		uint find_first(char);
		uint find_first(const char*);
		uint find_last(char);
		uint find_last(const char*);

		int compare(const char*);

		void append(char);
		void append(const char*);
};
