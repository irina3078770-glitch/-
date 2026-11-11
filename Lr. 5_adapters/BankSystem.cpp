#include "BankSystem.h"

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int inputInt(const char* msg) {
    int v;
    while (true) {
        cout << msg;
        if (cin >> v && (cin.peek() == '\n' || cin.peek() == ' ')) {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return v;
        }
        setColor(12); 
        cout << "Ошибка! Введите целое число.\n"; 
        setColor(7);
        cin.clear(); 
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
}

double inputDouble(const char* msg) {
    double v;
    while (true) {
        cout << msg;
        if (cin >> v && (cin.peek() == '\n' || cin.peek() == ' ')) {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return v;
        }
        setColor(12); 
        cout << "Ошибка! Введите корректное число.\n"; 
        setColor(7);
        cin.clear(); 
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
}

string inputString(const char* msg) {
    string str;
    while (true) {
        cout << msg;
        getline(cin, str);
        if (str.empty()) {
            setColor(12); cout << "Ошибка! Поле не может быть пустым.\n"; setColor(7);
            continue;
        }
        bool ok = true;
        for (int i = 0; i < str.length(); i++) {
            unsigned char c = str[i];
            if (c < 128 && !isalpha(c) && c != ' ') {
                ok = false;
                break;
            }
        }
        if (ok) return str;
        setColor(12); cout << "Ошибка! Только буквы и пробелы.\n"; setColor(7);
    }
}

string inputAlphanumericString(const char* msg) {
    string str;
    while (true) {
        cout << msg;
        getline(cin, str);
        if (!str.empty()) return str;
        setColor(12); 
        cout << "Ошибка! Значение не может быть пустым.\n"; 
        setColor(7);
    }
}

string inputDateString(const char* msg) {
    string date;
    while (true) {
        cout << msg;
        getline(cin, date);
        if (date.length() != 10 || date[2] != '.' || date[5] != '.') {
            setColor(12); cout << "Ошибка! Формат даты: ДД.ММ.ГГГГ (например, 16.10.2026).\n"; setColor(7);
            continue;
        }
        int day = atoi(date.substr(0, 2).c_str());
        int month = atoi(date.substr(3, 2).c_str());
        int year = atoi(date.substr(6, 4).c_str());
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1990 || year > 2026) {
            setColor(12); cout << "Ошибка! Проверьте корректность дня, месяца или года.\n"; setColor(7);
            continue;
        }
        return date;
    }
}

int generateUniqueIdForQueue(const queue<BankTransaction>& q) {
    int newId;
    bool exists;
    do {
        exists = false;
        newId = 1 + rand() % 9999;
        queue<BankTransaction> temp = q;
        while (!temp.empty()) {
            if (temp.front().getId() == newId) {
                exists = true;
                break;
            }
            temp.pop();
        }
    } while (exists);
    return newId;
}

int generateUniqueIdForStack(const stack<BankTransaction>& s) {
    int newId;
    bool exists;
    do {
        exists = false;
        newId = 1 + rand() % 9999;
        stack<BankTransaction> temp = s;
        while (!temp.empty()) {
            if (temp.top().getId() == newId) {
                exists = true;
                break;
            }
            temp.pop();
        }
    } while (exists);
    return newId;
}

int generateUniqueIdForPriorityQueue(const priority_queue<CreditApplication>& pq) {
    int newId;
    bool exists;
    do {
        exists = false;
        newId = 1 + rand() % 9999;
        priority_queue<CreditApplication> temp = pq;
        while (!temp.empty()) {
            if (temp.top().getId() == newId) {
                exists = true;
                break;
            }
            temp.pop();
        }
    } while (exists);
    return newId;
}


void QueueMenu() {
    queue<BankTransaction> q;
    int choice = 0;
    do {
        setColor(11);
        cout << "\n=========================================\n";
        cout << "           ОЧЕРЕДЬ ПЛАТЕЖЕЙ              \n";
        cout << "=========================================\n";
        setColor(7);
        cout << " " << setw(2) << left << "1." << " Показать очередь платежей\n"
            << " " << setw(2) << left << "2." << " Добавить платеж\n"
            << " " << setw(2) << left << "3." << " Обработать платеж\n"
            << " " << setw(2) << left << "4." << " Найти по ID\n"
            << " " << setw(2) << left << "5." << " Сохранить в файл\n" 
            << " " << setw(2) << left << "6." << " Загрузить из файла\n"
            << " " << setw(2) << left << "7." << " Редактировать сумму по ID\n"
            << " " << setw(2) << left << "8." << " Фильтрация по сумме\n"
            << " " << setw(2) << left << "0." << " Назад\n"
            
            << "-----------------------------------------\n";
        choice = inputInt("Ваш выбор: ");

        switch (choice) {
        case 1: {
            if (q.empty()) { 
                setColor(12); 
                cout << "Очередь пуста.\n"; 
                setColor(7); 
                break; 
            }
            queue<BankTransaction> temp = q;
            while (!temp.empty()) { 
                cout << temp.front() << "\n";
                temp.pop();
            }
            break;
        }
        case 2: {
            int id = generateUniqueIdForQueue(q);
            cout << "ID: " << id << "\n";
            double amt = inputDouble("Введите сумму (BYN): ");
            string date = inputDateString("Введите дату (ДД.ММ.ГГГГ): ");
            string acc = inputAlphanumericString("Введите номер счета: ");
            string clientName = inputString("ФИО клиента: ");
            q.push(BankTransaction(id, amt, date, acc, clientName));
            setColor(10);
            cout << "Добавлено.\n";
            setColor(7);
            break;
        }
        case 3: {
            if (q.empty()) { 
                setColor(12); 
                cout << "Очередь пуста.\n"; 
                setColor(7); 
                break;
            }
            setColor(14); 
            cout << "Обработана операция:\n";
            cout << q.front() << "\n";
            q.pop(); 
            setColor(7);
            break;
        }
        case 4: {
            if (q.empty()) { 
                setColor(12); 
                cout << "Очередь пуста.\n"; 
                setColor(7); 
                break; }
            int targetId = inputInt("Введите ID для поиска: ");
            queue<BankTransaction> temp = q;
            bool found = false;
            while (!temp.empty()) {
                if (temp.front().getId() == targetId) {
                    setColor(10); 
                    cout << "Найдено: "; 
                    setColor(7);
                    cout << temp.front() << "\n";
                    found = true;
                }
                temp.pop();
            }
            if (!found) { 
                setColor(12); 
                cout << "Операции с таким ID не найдено.\n"; 
                setColor(7); }
            break;
        }
        case 5: saveQueueToFile(q, "queue.txt"); break; 
        case 6: loadQueueFromFile(q, "queue.txt"); break;
        case 7: editQueueAmount(q); break;
        case 8: filterQueueByAmount(q); break;
        case 0: break;
        default: setColor(12); 
            cout << "Ошибка! Неверный выбор.\n"; 
            setColor(7);
        }
    } while (choice != 0);
}

void StackMenu() {
    stack<BankTransaction> s;
    int choice = 0;
    do {
        setColor(11);
        cout << "\n=========================================\n";
        cout << "            ИСТОРИЯ ОПЕРАЦИЙ                 \n";
        cout << "=========================================\n";
        setColor(7);
        cout << " " << setw(2) << left << "1." << " Показать историю\n"
            << " " << setw(2) << left << "2." << " Добавить операцию\n"
            << " " << setw(2) << left << "3." << " Отменить последнюю операцию\n"
            << " " << setw(2) << left << "4." << " Найти по ID\n"
            << " " << setw(2) << left << "5." << " Сохранить в файл\n"
            << " " << setw(2) << left << "6." << " Загрузить из файла\n"
            << " " << setw(2) << left << "7." << " Редактировать сумму по ID\n"
            << " " << setw(2) << left << "8." << " Фильтрация по сумме\n"
            << " " << setw(2) << left << "0." << " Назад\n"
            << "-----------------------------------------\n";
        choice = inputInt("Ваш выбор: ");

        switch (choice) {
        case 1: {
            if (s.empty()) { 
                setColor(12); 
                cout << "Операций не найдено.\n"; 
                setColor(7); 
                break;
            }
            stack<BankTransaction> temp = s;
            while (!temp.empty()) { 
                cout << temp.top() << "\n";
                temp.pop(); 
            }
            break;
        }
        case 2: {
            int id = generateUniqueIdForStack(s);
            cout << "ID: " << id << "\n";
            double amt = inputDouble("Введите сумму операции (BYN): ");
            string date = inputDateString("Введите дату (ДД.ММ.ГГГГ): ");
            string acc = inputAlphanumericString("Введите номер счета: ");
            string clientName = inputString("Введите ФИО клиента: ");
            s.push(BankTransaction(id, amt, date, acc, clientName));
            setColor(10); 
            cout << "Операция добавлена.\n"; 
            setColor(7);
            break;
        }
        case 3: {
            if (s.empty()) { 
                setColor(12); 
                cout << "Операций не найдено.\n";
                setColor(7); 
                break; 
            }
            setColor(10); 
            cout << "Отменено:\n";
            cout << s.top() << "\n";
            s.pop(); 
            setColor(7);
            break;
        }
        case 4: {
            if (s.empty()) { 
                setColor(12);
                cout << "Операций не найдено.\n"; 
                setColor(7); 
                break; 
            }
            int targetId = inputInt("Введиете ID для поиска: ");
            stack<BankTransaction> temp = s;
            bool found = false;
            while (!temp.empty()) {
                if (temp.top().getId() == targetId) {
                    setColor(10); 
                    cout << "Найдено: "; 
                    setColor(7);
                    cout << temp.top() << "\n";
                    found = true;
                }
                temp.pop();
            }
            if (!found) { 
                setColor(12); 
                cout << "Операция с таким ID не найдена.\n"; 
                setColor(7); }
            break;
        }
        case 5: saveStackToFile(s, "stack.txt"); break;
        case 6: loadStackFromFile(s, "stack.txt"); break;
        case 7: editStackAmount(s); break;
        case 8: filterStackByAmount(s); break;
        case 0: break;
        default: setColor(12); 
            cout << "Ошибка! Неверный выбор.\n"; 
            setColor(7);
        }
    } while (choice != 0);
}

void PriorityQueueMenu() {
    priority_queue<CreditApplication> pq;
    int choice = 0;
    do {
        setColor(11);
        cout << "\n=========================================\n";
        cout << "          КРЕДИТЫ            \n";
        cout << "=========================================\n";
        setColor(7);
        cout << " " << setw(2) << left << "1." << " Показать список кредитов\n"
            << " " << setw(2) << left << "2." << " Добавить заявку на кредит\n"
            << " " << setw(2) << left << "3." << " Одобрить кредит по максимальному приоритету\n"
            << " " << setw(2) << left << "4." << " Найти по ID\n"
            << " " << setw(2) << left << "5." << " Сохранить в файл\n"
            << " " << setw(2) << left << "6." << " Загрузить из файла\n"
            << " " << setw(2) << left << "7." << " Редактировать сумму по ID\n"
            << " " << setw(2) << left << "8." << " Фильтрация по сумме\n"
            << " " << setw(2) << left << "0." << " Назад\n"
            << "-----------------------------------------\n";
        choice = inputInt("Выбор: ");

        switch (choice) {
        case 1: {
            if (pq.empty()) { 
                setColor(12); 
                cout << "Кредиты не найдены.\n"; 
                setColor(7); 
                break; 
            }
            priority_queue<CreditApplication> temp = pq;
            while (!temp.empty()) { 
                cout << temp.top() << "\n";
                temp.pop();
            }
            break;
        }
        case 2: {
            int id = generateUniqueIdForPriorityQueue(pq);
            cout << "ID заявки: " << id << "\n";
            double amt = inputDouble("Введите сумму кредита (BYN): ");
            string date = inputDateString("Введите дату (ДД.ММ.ГГГГ): ");
            string acc = inputAlphanumericString("Введите номер счета: ");
            string clientName = inputString("Введите ФИО заявителя: ");
            int score;
            while (true) {
                score = inputInt("Введите рейтинг клиента (1-100): ");
                if (score >= 1 && score <= 100) {
                    break;
                }
                cout << "Ошибка! Рейтинг должен быть строго от 1 до 100. Попробуйте еще раз.\n";
            }

            pq.push(CreditApplication(id, amt, date, acc, clientName, score));
            setColor(10); 
            cout << "Заявка добавлена.\n"; 
            setColor(7);
            break;
        }
        case 3: {
            if (pq.empty()) { 
                setColor(12); 
                cout << "Кредиты не найдены.\n"; 
                setColor(7); 
                break;
            }
            setColor(10); 
            cout << "Одобрено:\n";
            cout << pq.top() << "\n";
            pq.pop(); 
            setColor(7);
            break;
        }
        case 4: {
            if (pq.empty()) { 
                setColor(12); 
                cout << "Кредиты не найдены.\n"; 
                setColor(7); 
                break; 
            }
            int targetId = inputInt("Введите ID для поиска: ");
            priority_queue<CreditApplication> temp = pq;
            bool found = false;
            while (!temp.empty()) {
                if (temp.top().getId() == targetId) {
                    setColor(10); 
                    cout << "Найдено: "; 
                    setColor(7);
                    cout << temp.top() << "\n";
                    found = true;
                }
                temp.pop();
            }
            if (!found) { 
                setColor(12);
                cout << "Кредит с таким ID не найден.\n"; 
                setColor(7); }
            break;
        }
        case 5: savePriorityQueueToFile(pq, "priority.txt"); break;
        case 6: loadPriorityQueueFromFile(pq, "priority.txt"); break;
        case 7: editPriorityQueueAmount(pq); break;
        case 8: filterPriorityQueueByAmount(pq); break;
        case 0: break;
        default: setColor(12);
            cout << "Ошибка! Неверный выбор.\n"; 
            setColor(7);
        }
    } while (choice != 0);
}

void saveQueueToFile(const queue<BankTransaction>& q, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        setColor(12); 
        cout << "Ошибка открытия файла для записи!\n"; 
        setColor(7);
        return;
    }
    queue<BankTransaction> temp = q;
    while (!temp.empty()) {
        const BankTransaction& tx = temp.front();
        outFile << tx.getId() << " " << tx.getAmount() << " " << tx.getDate() << " "
            << tx.getAccountNumber() << " " << tx.getClientName() << "\n";
        temp.pop();
    }
    outFile.close();
    setColor(10); 
    cout << "Данные сохранены в файл: " << filename << "\n"; 
    setColor(7);
}

void loadQueueFromFile(queue<BankTransaction>& q, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        setColor(12);
        cout << "Не удалось открыть файл для чтения.\n";
        setColor(7);
        return;
    }
    queue<BankTransaction> emptyQueue;
    q = emptyQueue;

    int id;
    double amount;
    string date, accNum;
    while (inFile >> id >> amount >> date >> accNum) {
        string clientName;
        inFile.ignore();
        getline(inFile, clientName);
        q.push(BankTransaction(id, amount, date, accNum, clientName));
    }
    inFile.close();
    setColor(10);
    cout << "Данные успешно загружены из файла: " << filename << "\n";
    setColor(7);
}

void saveStackToFile(const stack<BankTransaction>& s, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        setColor(12); 
        cout << "Ошибка открытия файла для записи!\n"; 
        setColor(7);
        return;
    }

    stack<BankTransaction> temp = s;
    vector<BankTransaction> vec;
    while (!temp.empty()) {
        vec.push_back(temp.top());
        temp.pop();
    }

    for (int i = vec.size() - 1; i >= 0; i--) {
        outFile << vec[i].getId() << " " << vec[i].getAmount() << " " << vec[i].getDate() << " "
            << vec[i].getAccountNumber() << " " << vec[i].getClientName() << "\n";
    }
    outFile.close();
    setColor(10); cout << "Данные сохранены в файл: " << filename << "\n";
    setColor(7);
}

void loadStackFromFile(stack<BankTransaction>& s, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        setColor(12); cout << "Не удалось открыть файл для чтения.\n";
        setColor(7);
        return;
    }
    stack<BankTransaction> emptyStack;
    s = emptyStack;

    int id;
    double amount;
    string date, accNum;
    vector<BankTransaction> vec;
    while (inFile >> id >> amount >> date >> accNum) {
        string clientName;
        inFile.ignore();
        getline(inFile, clientName);
        vec.push_back(BankTransaction(id, amount, date, accNum, clientName));
    }
    inFile.close();

    for (size_t i = 0; i < vec.size(); i++) {
        s.push(vec[i]);
    }
    setColor(10);
    cout << "Данные стека загружены из файла: " << filename << "\n";
    setColor(7);
}

void savePriorityQueueToFile(const priority_queue<CreditApplication>& pq, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) { 
        setColor(12); 
        cout << "Ошибка открытия файла!\n"; 
        setColor(7); 
        return; 
    }
    priority_queue<CreditApplication> temp = pq;
    while (!temp.empty()) {
        const CreditApplication& app = temp.top();
        outFile << app.getId() << " " << app.getAmount() << " " << app.getDate() << " "
            << app.getAccountNumber() << " " << app.getCreditScore() << " " << app.getClientName() << "\n";
        temp.pop();
    }
    outFile.close();
    setColor(10); 
    cout << "Заявки сохранены.\n"; 
    setColor(7);
}

void loadPriorityQueueFromFile(priority_queue<CreditApplication>& pq, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        setColor(12); cout << "Файл не найден.\n"; setColor(7);
        return;
    }
    priority_queue<CreditApplication> emptyPq;
    pq = emptyPq;

    CreditApplication app(0, 0.0, "", "", "", 0); 
    while (inFile >> app) {
        pq.push(app);
    }

    inFile.close();
    setColor(10); cout << "Заявки загружены.\n"; setColor(7);
}

void editQueueAmount(queue<BankTransaction>& q) {
    if (q.empty()) {
        setColor(12); cout << "Очередь пуста.\n"; setColor(7);
        return;
    }
    int targetId = inputInt("Введите ID операции для редактирования суммы: ");
    queue<BankTransaction> temp;
    bool found = false;

    while (!q.empty()) {
        BankTransaction tx = q.front();
        q.pop();
        if (tx.getId() == targetId) {
            double newAmt = inputDouble("Введите новую сумму (BYN): ");
            tx.setAmount(newAmt);
            found = true;
            setColor(10); cout << "Сумма успешно обновлена!\n"; setColor(7);
        }
        temp.push(tx);
    }
    q = temp;
    if (!found) {
        setColor(12); cout << "Операция с таким ID не найдена.\n"; setColor(7);
    }
}

void filterQueueByAmount(const queue<BankTransaction>& q) {
    if (q.empty()) {
        setColor(12); cout << "Очередь пуста.\n"; setColor(7);
        return;
    }
    double threshold = inputDouble("Введите минимальную сумму для фильтрации: ");
    setColor(11);
    cout << "\n--- Отфильтрованные операции (сумма >= " << threshold << " BYN) ---\n";
    setColor(7);

    queue<BankTransaction> temp = q;
    bool found = false;
    while (!temp.empty()) {
        if (temp.front().getAmount() >= threshold) {
            cout << temp.front() << "\n";
            found = true;
        }
        temp.pop();
    }
    if (!found) {
        setColor(12); cout << "Операций, удовлетворяющих условию, не найдено.\n"; setColor(7);
    }
}

void editStackAmount(stack<BankTransaction>& s) {
    if (s.empty()) {
        setColor(12); cout << "Стек пуст.\n"; setColor(7);
        return;
    }
    int targetId = inputInt("Введите ID операции для редактирования суммы: ");
    vector<BankTransaction> vec;
    bool found = false;

    while (!s.empty()) {
        vec.push_back(s.top());
        s.pop();
    }

    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i].getId() == targetId) {
            double newAmt = inputDouble("Введите новую сумму (BYN): ");
            vec[i].setAmount(newAmt);
            found = true;
            setColor(10); cout << "Сумма успешно обновлена!\n"; setColor(7);
        }
    }

    for (int i = vec.size() - 1; i >= 0; i--) {
        s.push(vec[i]);
    }

    if (!found) {
        setColor(12); cout << "Операция с таким ID не найдена.\n"; setColor(7);
    }
}

void filterStackByAmount(const stack<BankTransaction>& s) {
    if (s.empty()) {
        setColor(12); cout << "Стек пуст.\n"; setColor(7);
        return;
    }
    double threshold = inputDouble("Введите минимальную сумму для фильтрации: ");
    setColor(11);
    cout << "\n--- Отфильтрованная история (сумма >= " << threshold << " BYN) ---\n";
    setColor(7);

    stack<BankTransaction> temp = s;
    vector<BankTransaction> vec;
    while (!temp.empty()) {
        vec.push_back(temp.top());
        temp.pop();
    }

    bool found = false;
    for (int i = vec.size() - 1; i >= 0; i--) {
        if (vec[i].getAmount() >= threshold) {
            cout << vec[i] << "\n";
            found = true;
        }
    }
    if (!found) {
        setColor(12); cout << "Операций, удовлетворяющих условию, не найдено.\n"; setColor(7);
    }
}

void editPriorityQueueAmount(priority_queue<CreditApplication>& pq) {
    if (pq.empty()) {
        setColor(12); cout << "Список кредитов пуст.\n"; setColor(7);
        return;
    }
    int targetId = inputInt("Введите ID заявки для редактирования суммы: ");
    vector<CreditApplication> vec;
    bool found = false;

    while (!pq.empty()) {
        vec.push_back(pq.top());
        pq.pop();
    }

    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i].getId() == targetId) {
            double newAmt = inputDouble("Введите новую сумму кредита (BYN): ");
            vec[i].setAmount(newAmt);
            found = true;
            setColor(10); cout << "Сумма заявки успешно обновлена!\n"; setColor(7);
        }
        pq.push(vec[i]);
    }

    if (!found) {
        setColor(12); cout << "Заявка с таким ID не найдена.\n"; setColor(7);
    }
}

void filterPriorityQueueByAmount(const priority_queue<CreditApplication>& pq) {
    if (pq.empty()) {
        setColor(12); cout << "Список кредитов пуст.\n"; setColor(7);
        return;
    }
    double threshold = inputDouble("Введите минимальную сумму для фильтрации: ");
    setColor(11);
    cout << "\n--- Отфильтрованные кредиты (сумма >= " << threshold << " BYN) ---\n";
    setColor(7);

    priority_queue<CreditApplication> temp = pq;
    bool found = false;
    while (!temp.empty()) {
        if (temp.top().getAmount() >= threshold) {
            cout << temp.top() << "\n";
            found = true;
        }
        temp.pop();
    }
    if (!found) {
        setColor(12); cout << "Заявок, удовлетворяющих условию, не найдено.\n"; setColor(7);
    }
}