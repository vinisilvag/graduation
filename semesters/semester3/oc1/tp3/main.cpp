// Vinicius Silva Gomes - 2021421869
// Mirna Mendonça e Silva - 2021421940
// Matheus Vaz Leal Lima - 2020109985

#include <bits/stdc++.h>
#include <bitset>
#include <string>

using namespace std;

#define _                                                                      \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);

#define endl '\n'

class Row {
protected:
  static int nextTimestamp;

private:
  uint32_t address;
  int val = 0;
  int timestamp;

public:
  Row();
  Row(uint32_t address);
  int getValidity();
  uint32_t getAddress();
  int getTimestamp();
};

int Row::nextTimestamp = -1;

Row::Row() {}

Row::Row(uint32_t address) {
  this->address = address;
  this->timestamp = ++this->nextTimestamp;
  this->val = 1;
}

int Row::getValidity() { return this->val; }

uint32_t Row::getAddress() { return this->address; }

int Row::getTimestamp() { return this->timestamp; }

class Cache {
private:
  uint32_t size, rowSize, groupSize;
  int rowNumber;
  vector<Row> rows;

public:
  Cache(uint32_t cacheSize, uint32_t rowSize, uint32_t groupSize);
  uint32_t getRowSize();
  void show();
  void insert(uint32_t address);
};

uint32_t Cache::getRowSize() { return this->rowSize; }

void Cache::insert(uint32_t address) {
  Row data = Row(address);

  if (groupSize == 1) {
    // Mapeamento direto
    int idx = address % rowNumber;
    rows[idx] = data;
  } else if (rowNumber == int(groupSize)) {
    // Totalmente associativa
    bool inserted = false;

    for (int i = 0; i < rowNumber; i++) {
      if (!rows[i].getValidity()) {
        rows[i] = data;
        inserted = true;
        break;
      }
    }

    int minTimestamp = -1;
    int minIndex = -1;

    if (!inserted) {
      for (int i = 0; i < rowNumber; i++) {
        if (rows[i].getTimestamp() < minTimestamp) {
          minTimestamp = rows[i].getTimestamp();
          minIndex = i;
        }
      }

      rows[minIndex] = data;
    }
  } else {
    int nWays = rowNumber / groupSize;
    int nBits = log2(nWays);
    bool inserted = false;

    uint32_t idx = address;

    idx &= ~(~0 << nBits);

    for (int i = idx * groupSize; i < (idx + 1) * groupSize; i++) {
      if (!rows[i].getValidity()) {
        rows[i] = data;
        inserted = true;
        break;
      }
    }

    int minTimestamp = -1;
    int minIndex = -1;

    if (!inserted) {
      for (int i = (idx - 1) * groupSize; i < idx * groupSize; i++) {
        if (rows[i].getTimestamp() < minTimestamp) {
          minTimestamp = rows[i].getTimestamp();
          minIndex = i;
        }
      }

      rows[minIndex] = data;
    }
  }
}

Cache::Cache(uint32_t cacheSize, uint32_t rowSize, uint32_t groupSize) {
  this->size = cacheSize;
  this->rowSize = rowSize;
  this->groupSize = groupSize;
  this->rowNumber = cacheSize / rowSize;

  rows.resize(this->rowNumber);
}

void Cache::show() {
  cout << "================" << endl;
  cout << "IDX V ** ADDR **" << endl;

  for (int i = 0; i < rowNumber; i++) {
    cout << setfill('0') << setw(3) << i << " " << rows[i].getValidity();

    if (rows[i].getValidity())
      cout << " 0x" << hex << setfill('0') << setw(8) << uppercase
           << rows[i].getAddress();

    cout << endl;
  }

  cout << endl;
}

int main() {
  uint32_t cacheSize, rowSize, groupSize;
  string fileName;

  cin >> cacheSize >> rowSize >> groupSize >> fileName;

  Cache *cache = new Cache(cacheSize, rowSize, groupSize);

  ifstream file(fileName);

  if (file.is_open()) {
    string line;
    stringstream ss;

    while (getline(file, line)) {
      // cout << line << endl; // 0xDEADBEEF                // 0x12345678
      uint32_t number;
      istringstream iss(line);
      iss >> hex >> number;
      int shift = int(log2(double(cache->getRowSize())));

      // cout << number << endl;

      number = number >> shift;

      // cout << hex << number << endl; //0x0037AB6F (3648367dec) //0x00048D15
      // (298261dec)

      cache->insert(number);

      cache->show();
    }
  } else {
    cout << "Error reading the file!" << endl;
  }

  return 0;
}
