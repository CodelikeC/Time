#include <iostream>
#include <string>
using namespace std ; 
class Date 
{
protected:
    int year;
    int month;
    int day;

public:
    Date(int year, int month, int day) : year(year), month(month), day(day) {}
    // gán tham số vào thuộc tính được khởi tạo // 
    bool operator==(const Date& other) const 
    {
        return (year == other.year && month == other.month && day == other.day);
        // trả về năm, tháng và ngày // 
    }
};

class Time {
protected:
    int hour;
    int minute;
    int second;

public:
    Time(int hour, int minute, int second) : hour(hour), minute(minute), second(second) {}

    bool operator==(const Time& other) const 
    {
        return (hour == other.hour && minute == other.minute && second == other.second);
        // trả về hour, day , minute và second // 
    }
};

class DateTime : public Date, public Time 
{
public:
    DateTime(int year, int month, int day, int hour, int minute, int second)
        : Date(year, month, day), Time(hour, minute, second) {}

    bool operator==(const DateTime& other) const 
    {
        return (Date::operator==(other) && Time::operator==(other));
    }

    DateTime operator+(const DateTime& other) const 
    {
        int newYear = year + other.year; // tính ra năm // 
        int newMonth = month + other.month; // tính ra tháng // 
        int newDay = day + other.day; // tính thêm ngày // 
        int newHour = hour + other.hour; // tính thêm giờ // 
        int newMinute = minute + other.minute; // tính thêm phút // 
        int newSecond = second + other.second; // tính thêm giây // 

        // Adjust the values if they exceed the valid range
        if (newSecond >= 60) 
        {
            newMinute += newSecond / 60;
            newSecond %= 60;
        }
        if (newMinute >= 60) {
            newHour += newMinute / 60;
            newMinute %= 60;
        }
        if (newHour >= 24) {
            newDay += newHour / 24;
            newHour %= 24;
        }
        if (newDay > 31) {
            newMonth += newDay / 31;
            newDay %= 31;
        }
        if (newMonth > 12) {
            newYear += newMonth / 12;
            newMonth %= 12;
        }

        return DateTime(newYear, newMonth, newDay, newHour, newMinute, newSecond);
    }

    string serializeToString() const 
    {
        // Format: YYYY-MM-DD HH:MM:SS
        string serializedDateTime =
            to_string(year) + "-" + padZero(month) + "-" + padZero(day) + " " +
            padZero(hour) + ":" + padZero(minute) + ":" + padZero(second);

        return serializedDateTime;
    }

private:
    string padZero(int value) const {
        if (value < 10) {
            return "0" + to_string(value);
        }
        return to_string(value);
    }
};

int main() 
{
    DateTime dt1(2024, 4, 3, 10, 30, 15); // truyền vào giá trị của đối tượng dt1 đại diện cho các thuộc tính thuộc lớp datetime // 
    DateTime dt2(2024, 4, 3, 5, 45, 20);

    if (dt1 == dt2) 
    {
        cout << "DateTime objects are equal." << endl;
    } 
    else 
    {
        cout << "DateTime objects are not equal." << endl;
    }

    DateTime dt3 = dt1 + dt2;
    cout << "Added DateTime: " << dt3.serializeToString() << endl;

    string serializedDateTime = dt1.serializeToString();
    cout << "Serialized DateTime: " << serializedDateTime << endl;

    return 0;
}
// Dòng này là một phần của hàm tạo (constructor) của lớp `Time`. Nó được sử dụng để khởi tạo các thành viên dữ liệu (`hour`, `minute`, `second`) của lớp `Time` bằng các giá trị được truyền vào qua tham số của hàm tạo.

