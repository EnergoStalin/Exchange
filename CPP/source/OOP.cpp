#ifndef nullptr
#define nullptr 0
#endif
//nullptr
//Include Defines:
//FriendlyFunctions
//DEBUG
//MyClass
//Point
//String
//MyClass2
//AppleClass
//ImageClass
//IterableClass
//PixelClass
//VirtualAndAbstract
//Deligation
//MoreExtend
//Interface
//Pixel_Overloaded_Output_Input
//Vector2DClass

#ifdef MyClass
class MyClass {
	public:
		int *data;
		MyClass(int d) {
			this->size = d;
			this->data = new int[d];	
			for(int i = 0; i < d; i++) {
				this->data[i] = i;
			}
			cout << "missed " << this << " missed " << d << endl;
		}
		MyClass(const MyClass &other) {
			this->size = other.size;
			this->data = new int[this->size];
			for(int i = 0; i < other.size; i++) {
				this->data[i] = other.data[i];
			}
			cout << " " << this << endl;
		}
		MyClass & operator = (const MyClass &other) {
			cout << " " << this << endl;
			this->size = other.size;
			if(this->data != nullptr) {
				delete []this->data;
			}
			this->data = new int[this->size];
			for(int i = 0; i < this->size; i++) {
				this->data[i] = other.data[i];
			}
			return *this;
		}
		~MyClass() {
			cout << "missed " << this << endl;
			delete []data;
		}
		private:
			int size;
};
#endif
#ifdef Point
class Point {
	public:
		Point(int x, int y) {
			this->x = x;
			this->y = y;
		}
		Point() {
			this->x = 0;
			this->y = 0;
		}
		#ifdef DEBUG
		void print() {
			cout << "X: " << this->x << "\tY: " << this->y << "\tAddres: " << this << endl;
		}
		void print(char *id) {
			cout << "Point " << id << " - X: " << this->x << ", Y: " << this->y << ", Addres: " << this << endl;
		}
		void print(char *id, char *desc) {
			cout << "Point " << id << " - X: " << this->x << ", Y: " << this->y << ", Addres: " << this << endl;
			cout << "Description:\n" << desc << endl;
		}
		#endif //DEBUG
		bool operator == (const Point &other) {
			return this->x == other.x && this->y == other.y;
		}
		bool operator != (const Point &other) {
			return !(*this == other);
		}
		Point & operator = (const Point &other) {
			this->x = other.x;
			this->y = other.y;
			return *this;
		}
		Point & operator ++() {
			this->x++;
			this->y++;
			return *this;
		}
		Point & operator ++(int value) {
			Point temp(*this);
			
			this->x++;
			this->y++;
			return temp;
		}
		Point & operator --() {
			this->x--;
			this->y--;
			return *this;
		}
		Point & operator --(int value) {
			Point temp(*this);
			
			this->x--;
			this->y--;
			return temp;
		}
		Point operator + (const Point &other) {
			Point temp(this->x + other.x, this->y + other.y);
			return temp;
		}
		int & operator[](int i) {
			switch(i) {
				case 0: return x;
				case 1: return y;
				default: cout << "Invalid param" << endl;
			}
		}
		#ifdef FriendlyFunctions
		friend void ChangeX(Point &value); //Changes X always -1
		#endif
	private:
		int x;
		int y;
};
#endif
#ifdef String
int strlen(char *str) {
	int len = 0;
	while(str[len] != '\0') {
		len++;
	}
	return len;
}
class String {
	public:
		String() {
			str = nullptr;
		}
		String(char *str) {
			int len = strlen(str);
			this->str = new char[len + 1];
			for(int i = 0; i < len; i++) {
				this->str[i] = str[i];
			} this->str[len] = '\0';
			#ifdef DEBUG
				cout << "String length " << len << '.' << endl;
			#endif //DEBUG
		}
		String(const String &other) {
			if(this->str != nullptr) delete []this->str;
			int len = strlen(other.str);
			this->str = new char[len + 1];
			for(int i = 0; i < len; i++) {
				this->str[i] = other.str[i];
			} this->str[len] = '\0';
		}
		~String() {
			if(str != nullptr) delete []str;
		}
		String & operator = (const String &other) {
			if(this->str != nullptr) delete []this->str;
			int len = strlen(other.str);
			this->str = new char[len + 1];
			for(int i = 0; i < len; i++) {
				this->str[i] = other.str[i];
			} this->str[len] = '\0';
			
			return *this;
		}
		String operator + (const String &other) {
			String NewStr = new char[strlen(this->str) + strlen(other.str) + 1];
			int i = 0;
			for(; i < strlen(this->str); i++) {
				NewStr.str[i] = other.str[i];
			}
			for(int j = 0; j < strlen(other.str); j++, i++) {
				NewStr.str[i] = other.str[j];
			} NewStr.str[i] = '\0';
			
			return NewStr;
		}
		void print() {
			cout << str;
		}
		char *c_str() {
			if(this->str == nullptr) return '\0';
			return this->str;
		}
		int length() {
			if(this->str == nullptr) return 0;
			int len = 0;
			while(this->str[len] != '\0') len++;
			return len;
		}
	private:
		char *str;
};
#endif

#ifdef FriendlyFunctions
//Friendly Functions

void ChangeX(Point &value) { //Friendly for class Point
	value.x = -1;
}
#endif

#ifdef MyClass2
class MyClass {
	public:
		void PrintMessage();
};
void MyClass::PrintMessage() {
	cout << "Hello" << endl;
}
#endif
#ifdef AppleClass
class Apple;
class Human {
	public:
		void TakeApple(Apple &apple);
		void EatApple(Apple &apple);
};
class Apple {
	friend Human;
	public:
		static int Count;
		Apple(int weight = 0, string color = "red") {
			this->weight = weight;
			this->color = color;
			Apple::Count++;
		}
	private:
		int weight;
		string color;
		void del() {
			this->weight = 0;
			this->color = "undefined";
		}
	friend void Human::TakeApple(Apple &apple);
};
int Apple::Count = 0;
void Human::TakeApple(Apple &apple) {
	 cout << "Apple taked:\nWeight: " << apple.weight << "\nColor: " << apple.color << '\n';
}
void Human::EatApple(Apple &apple) {
	cout << "Apple Eated\n";
	apple.del();
}
#endif
#ifdef IterableClass
class Iterable {
	public:
		static int TotalCount;
		int id;
		Iterable() {
			TotalCount++;
			this->id = TotalCount;
		}
};
int Iterable::TotalCount = 0;
#endif
#ifdef ImageClass
class Image {
	public:
		void GetImageInfo() {
			for(int i = 0; i < square; i++) {
				cout << pix[i].GetInfo() << endl;
			}
		}
	private:
		class Pixel : public Iterable {
			public:
				Pixel(int r = 0, int g = 0, int b = 0) {
					this->r = r;
					this->g = g;
					this->b = b;
					this->id = Pixel::TotalCount;
				}
				string GetInfo() {
					return "Pixel " + to_string(this->id) + " :\nR: " +
						to_string(this->r) + 
						"\nG: " + to_string(this->g) +
						"\nB: " + to_string(this->b);
				}
			private:
				int r;
				int g;
				int b;
		};
	static const int square = 5;
	Pixel pix[square] 
	{
		Pixel(0,4,64),
		Pixel(10,42,6),
		Pixel(30,14,64),
		Pixel(12,44,164),
		Pixel(60,24,84)
	};
};
#endif
#ifdef PixelClass
class Pixel : public Iterable {
	public:
		Pixel(int r = 0, int g = 0, int b = 0) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->id = Pixel::TotalCount;
		}
		~Pixel() {
			cout << "Destructor was called for Px #" << this->id << endl;
		}
		string GetInfo() {
			return "Pixel " + to_string(this->id) + " :\nR: " +
				to_string(this->r) + 
				"\nG: " + to_string(this->g) +
				"\nB: " + to_string(this->b);
		}
	private:
		int r;
		int g;
		int b;
};
#endif
#ifdef VirtualAndAbstract
class Weapon {
	public:
	virtual void Shoot() = 0;
};
class Knife : public Weapon {
	public:
	void Shoot() override {
		cout << "VJUH!!!" << endl;
	}
};
class Bazooka : public Weapon {
	public:
		void Shoot() override {
			cout << "BADABUM!!!" << endl;
		}
};
class Gun : public Weapon {
	public:
		virtual void Shoot() {
			cout << "Bang!!!" << endl;
		}
};
class SubMachineGun : public Gun {
	public:
		void Shoot() override {
			cout << "Bang!!!\n" << "Bang!!!\n" << "Bang!!!\n" << endl;
		}
};
class Player {
	public:
		void Shoot(Weapon *weapon) {
			weapon->Shoot();
		}
};
class A {
	public:
	A(int count) {
		this->arr = new int [count];
		ArrayTools::FillIntArray(this->arr, count);
		ArrayTools::ShowArray(this->arr,count);
	}
	virtual ~A() {
		delete[] arr;
		cout << "Memory A free" << endl;
	}
	private:
	 int *arr;
};
class B : public A {
	public:
	B(int count) : A(count) {
		this->arr2 = new int [count];
		ArrayTools::FillIntArray(this->arr2, count);
		ArrayTools::ShowArray(this->arr2,count);
	}
	~B() override {
		delete[] arr2;
		cout << "Memory B free" << endl;
	}
	private:
	 int *arr2;
};
class AAD {
	public:
	AAD() {}
	virtual ~AAD() = 0;
};
AAD::~AAD() {};
#endif
#ifdef Deligation
class Human {
	public:
	Human() { //Syntax Shugar
		this->name = "Unnamed";
		this->age = 0;
		this->weight = 0;
	}
	Human(string name) : Human() { this->name = name; }
	Human(string name, int age) : Human(name) { this->age = age; }
	Human(string name, int age, int weight) : Human(name, age) { this->weight = weight; }
	string GetInfo() {
		return "Name: " +
		this->name + 
		"\nAge: " +
		to_string(this->age) +
		"\nWeight: " +
		to_string(this->weight) +
		'\n';
	}

	string name;
	int age;
	int weight;
};
class Msg {
	public:
		Msg(string msg) {
			this->msg = msg;
		}
		virtual string GetMsg() {
			return msg;
		}
	private:
	string msg;
};
class BracketsMsg : public Msg { //Important
	public:
	BracketsMsg(string msg) : Msg(msg) {}
	string GetMsg() override {
		return "[" + ::Msg::GetMsg() + "]";
	}
};
class Printer {
	public:
	void Print(Msg *msg) {
		cout << msg->GetMsg() << endl;
	}
};
#endif
#ifdef MoreExtend
class Car {
	public:
	Car() {
		cout << "Called constructor Car." << endl;
	}
	~Car() {
		cout << "Called destructor Car." << endl;
	}
	void Use() {
		cout << "I ride." << endl;
	}
};
class Airplane {
	public:
	Airplane() {
		cout << "Called constructor Airplane." << endl;
	}
	~Airplane() {
		cout << "Called destructor Airplane." << endl;
	}
	void Use() {
		cout << "I Fly." << endl;
	}
};
class FlyingCar : public Car, public Airplane {
	public:
	FlyingCar() {
		cout << "Called constructor FlyingCar." << endl;
	}
	~FlyingCar() {
		cout << "Called destructor FlyingCar." << endl;
	}
};
#endif
#ifdef Vector2DClass
#include <math.h>
class Coord {
	public:
		Coord(int x,int y) {
			this->x = x;
			this->y = y;
		}
		Coord() {
			this->x = 0;
			this->y = 0;
		}
		Coord operator+(Coord o) {
			return Coord(this->x += o.x, this->y += o.y);
		}
		Coord operator=(const Coord &c) {
			this->x = c.x;
			this->y = c.y;
		}
		double to(const Coord &c) {
			return sqrt(pow((double)(this->x - c.x),2) + pow((double)(this->y - c.y),2));
		}
		int getX() {
			return x;
		}
		int getY() {
			return y;
		}
		void setX(int x) {
			this->x = x;
		}
		void setY(int y) {
			this->y = y;
		}
	private:
		int x;
		int y;
		friend ostream& operator<<(ostream &os, const Coord &c);
		friend istream& operator>>(istream &is, Coord &c);
};
class Vector2D {
	public:
		Vector2D(int bx,int by, int ex, int ey) {
			this->begin = Coord(bx,by);
			this->end = Coord(ex,ey);
		}
		Vector2D(Coord begin, Coord end) {
			this->begin = begin;
			this->end = end;
		}
		Vector2D() {
			this->begin = Coord();
			this->end = Coord();
		}
		Vector2D operator+(const Vector2D &o) {
			return Vector2D(this->begin + o.begin,this->end + o.end);
		}
		Vector2D operator=(const Vector2D &o) {
			this->begin = o.begin;
			this->end = o.end;
		}
	private:
		Coord begin;
		Coord end;
		friend ostream& operator<<(ostream &os, const Vector2D &v);
};
ostream& operator<<(ostream &os, const Vector2D &v) {
	os << "Begin:\n" << v.begin << "\nEnd:\n" << v.end;
}
ostream& operator<<(ostream &os, const Coord &c) {
	os << "X: " << c.x << "\nY: " << c.y;
}
istream& operator>>(istream &is, Coord &c) {
	cout << "Input x, y separate by space: ";
	is >> c.x >> c.y;
}
#endif
#ifdef Interface
class Ibicycle {
public:
	void virtual EwistTheWheel() = 0;
	void virtual Ride() = 0;
	void virtual Drop() = 0;
};

class Bicycle : public Ibicycle {
public:
	void EwistTheWheel() override {
		cout << "Wist the simple wheel." << endl;
	}
	void Ride() override {
		cout << "Vjhhhh 100%!!!" << endl;
	}
	void Drop() override {
		cout << "Bamm!!!(Bicycle is dropped)" << endl;
	}
};

class SportBicycle : public Ibicycle {
public:
	void EwistTheWheel() override {
		cout << "Wist the sport wheel." << endl;
	}
	void Ride() override {
		cout << "Vjhhhh 120%!!!" << endl;
	}
	void Drop() override {
		cout << "Badabum!!!(Sport bicycle is dropped)" << endl;
	}
};

class Human {
public:
	void RideOn(Ibicycle &b) {
		cout << "Sit on." << endl;
		b.EwistTheWheel();
		cout << "go Go GO!!!" << endl;
		b.Ride();
	}
	void Drop(Ibicycle &b) {
		b.Drop();
	}
};
#endif
#ifdef Pixel_Overloaded_Output_Input
class Pixel {
public:
	Pixel() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
	}
	Pixel(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	void FillFromConsole() {
		cout << "Введите значение красного цвета: ";
		cin >> this->r;
		cout << "Введите значение зелёного цвета: ";
		cin >> this->g;
		cout << "Введите значение голубого цвета: ";
		cin >> this->b;
	}
private:
	int r;
	int g;
	int b;
	friend ostream& operator<<(ostream& os, const Pixel& pix);
	friend istream& operator>>(istream& is, Pixel& pix);
};


ostream& operator<<(ostream& os, const Pixel& pix) {
	os << pix.r << " " << pix.g << " " << pix.b << " ";

	return os;
}

istream& operator>>(istream& is, Pixel& pix) {
	is >> pix.r >> pix.g >> pix.b;

	return is;
}
#endif