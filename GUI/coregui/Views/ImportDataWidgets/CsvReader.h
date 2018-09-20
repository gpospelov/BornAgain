#ifndef CSVREADER_H
#define CSVREADER_H

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class CSVRow
{
    public:
        string const& operator[](unsigned index) const;

        unsigned long size() const;

        void readNextRow(istream& str);


        void setSeparator(char sep);

        char getSeparator();

        void addCell(string str);

        vector<string> dataVector(){return m_data;}

    private:
        vector<string>    m_data;
        char separator = '-';
};

inline istream& operator>>(istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

class CSVIterator
{
    public:
        typedef input_iterator_tag     iterator_category;
        typedef CSVRow                      value_type;
        typedef unsigned long                difference_type;
        typedef CSVRow*                     pointer;
        typedef CSVRow&                     reference;

        CSVIterator(istream& str, char sep)  :m_str( str.good() ? &str : nullptr ) {m_sep=sep; ++(*this); }
        CSVIterator()                   :m_str(nullptr) {}

        // Pre Increment
        CSVIterator& operator++()               {if (m_str) { m_row.setSeparator(m_sep); if (!((*m_str) >> m_row)){m_str = nullptr;}}return *this;}
        // Post increment
        CSVIterator operator++(int)             {CSVIterator    tmp(*this);++(*this);return tmp;}
        CSVRow const& operator*()   const       {return m_row;}
        CSVRow const* operator->()  const       {return &m_row;}

        bool operator==(CSVIterator const& rhs) {return ((this == &rhs) || ((this->m_str == nullptr) && (rhs.m_str == nullptr)));}
        bool operator!=(CSVIterator const& rhs) {return !((*this) == rhs);}



    private:
        istream*       m_str;
        CSVRow              m_row;
        char                m_sep;
};

class CSVFile
{
    public:
        CSVFile(string path_to_file): filepath(path_to_file) {Init();}
        CSVFile(string path_to_file, char sep): filepath(path_to_file), separator(sep) {Init();}
        CSVFile(string path_to_file, char sep, unsigned headRow): filepath(path_to_file), separator(sep), headersRow(headRow) {Init();}


        void Init();

        void Read();


        void EqualizeRowLengths();


        vector<string> const operator[](unsigned index_i) const;

        unsigned long NumberOfRows() const;

        unsigned long NumberOfColumns() const;

        void set_separator(char sep);

        char get_separator();

        CSVRow get_headers();

        CSVRow get_row(unsigned i);

        vector<vector<string>> asArray(){return m_data;}

    private:
        string filepath;
        char separator = '-';
        unsigned headersRow = 0;
        unsigned numberOfColumns = 0;
        vector<CSVRow>    rows;
        vector<vector<string>>    m_data;

};

#endif // CSVREADER_H
