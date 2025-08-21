#include <iostream>
#include <string.h>

class String
{
public:
    String();

    String(const char *pstr);

    String(const String &rhs);

    String &operator=(const String &rhs);

    ~String();

    String(String &&rhs);

    String &operator=(String &&rhs);


    String &operator+=(const String &);
	String &operator+=(const char *);
	
	char &operator[](std::size_t index);
	const char &operator[](std::size_t index) const;
	
	std::size_t size() const;
	const char* c_str() const;
	
	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);
	
	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);
	
	friend std::ostream &operator<<(std::ostream &os, const String &lhs);
	friend std::istream &operator>>(std::istream &is, String &lhs);

private:
    char *_pstr;
};

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);
