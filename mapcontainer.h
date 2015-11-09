#ifndef MAPCONTAINER_H
#define MAPCONTAINER_H

#include <map>

using namespace std;

template <typename KEY, typename TYPE>
class MapContainer
{
public:

    inline MapContainer() {}

    inline ~MapContainer() {
        erase();
    }

    inline void addElement(KEY key, TYPE value){
        mapContainer[key] = value;
        count++;
    }

    inline TYPE getElement(KEY key)
    {
        return mapContainer[key];
    }


    inline void removeElement(KEY key){
        typename map<KEY, TYPE>::iterator it = mapContainer.find(key);

        if(std::is_pointer<TYPE>::value)
            delete it->second;

        mapContainer.erase(it);
        count--;

        if(std::is_pointer<KEY>::value)
            delete it->second;

    }


    inline bool isPresent(KEY key){
        return mapContainer.count(key);
    }


    inline void erase(){
        typename map<KEY, TYPE>::iterator it;
        TYPE temp;

        for (it=mapContainer.begin(); it != mapContainer.end(); it++){

            temp = it->second;
            if(std::is_pointer<TYPE>::value)
                delete temp;

            if(std::is_pointer<KEY>::value)
                delete it->second;

        }

        mapContainer.erase(mapContainer.begin(), mapContainer.end());
        count = 0;
    }

    inline map<KEY, TYPE> &getContainer(){
        return mapContainer;
    }


    inline int getCount() const{
        return count;
    }

private:
    map<KEY, TYPE> mapContainer;
    int count;
};

#endif // MAPCONTAINER_H
