
friend istream& operator>>(istream& is, className& object);  //перегрузка оператора ввода

cout.setf(ios::flags)  //установка флага (goodbit, eofbit, failbit, badbit)
cout.unsetf(ios::flags)
cout.setf(ios::oct)  //пример

cout.setf(ios::flag1 | ios::flag2 | ios::flag3)  //установка нескольких флагов

std::cout << std::hex << // использование манипуляторов

ifstream infile("fdata.txt");//создание объекта типа ifstream

ofstream os("Data.txt", ios::binary);//создание выходного байтового потока
os.write(reinterpret_cast<char*>(buff), MAX * sizeof(int)); //запись данных в бинарный файл


