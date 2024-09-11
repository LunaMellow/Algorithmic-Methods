/**     Description:
*      - Abstract datatype Map
 *
 *      @file Task 2.cpp
 *      @date 8/29/2024
 *
 *      @author Luna S.
 *      @alias LunaMellow
 */

#include <iostream>
#include <string>

using namespace std;

template <typename T1, typename T2>
class Map {
private:
	T1* keyer;
	T2* data;
	int kapasitet{}, antall{};

public:
	explicit Map(const int lengde = 200) {	keyer = new T1[lengde];
		data  = new T2[lengde];
		kapasitet = lengde; antall = 0; }

	~Map() { delete[] keyer; delete[] data; }

	void change(const T1 key, const T2 dat) {
		int i;
		if (find(key)) {
			for (i = 0; i < antall; i++)
				if (keyer[i] == key) break;
			data[i] = dat;
		} else
			cout << "\nKey doesn't exist!\n\n";
	}

	void display() {
		for (int i = 0; i < antall; i++) {
			cout << '\t' << keyer[i] << ": " << data[i] << '\n';
			cout << "\n\tAntall keyer m/data i map'en: " << antall << '\n';
		}
	}

    void erase(const T1 key) {
        int i;
        if (find(key)) {
            for (i = 0; i < antall; i++)
                if (keyer[i] == key)  break;
            antall--;
            for (int j = i; j < antall; j++) {
                keyer[j] = keyer[j+1];
                data[j] = data[j+1];
            }
        } else
          cout << "\nKey doesn't exists!\n\n";
	}


    bool find(const T1 key) const {

		for (int i = 0;  i < antall;  i++)
			if (keyer[i] == key)  return true;
		return false;
	}

    T2 get(const T1 key) const {

		for (int i = 0;  i < antall;  i++)
			if (keyer[i] == key)  return data[i];
		return T2();
	}

    void insert(const T1 key, const T2 dat) {
        int nyIndeks = 0;
        if (!find(key)) {
           if (antall < kapasitet) {
               while (nyIndeks < antall  &&  keyer[nyIndeks] < key)
                     nyIndeks++;
               antall++;
               for (int i = antall-1;  i > nyIndeks;  i--) {
                   keyer[i] = keyer[i-1];
                   data[i] = data[i-1];
               }
               keyer[nyIndeks] = key;
               data[nyIndeks] = dat;
           } else
             cout << "\nMap is already full!\n\n";
        } else
            cout << "\nKey already exists!\n\n";
    }
    int size() const  {  return antall;  }
};