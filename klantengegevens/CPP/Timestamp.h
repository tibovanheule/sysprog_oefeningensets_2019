#ifndef TIMESTAMP_H
#define TIMESTAMP_H
class Timestamp{
    public:
        int getDay();
        int getMonth();
        int getYear();
        void setDay(int d);
        void setMonth(int d);
        void setYear(int d);
        Timestamp();
        Timestamp(int day, int month, int year);
        Timestamp(Timestamp &timestamp);
        ~Timestamp();
    private:
        int day;
        int month;
        int year;
};
#endif