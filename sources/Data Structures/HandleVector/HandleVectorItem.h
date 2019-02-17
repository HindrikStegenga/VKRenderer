//
// Created by hindrik on 16-2-19.
//

#ifndef VKRENDERER_HANDLE_VECTOR_ITEM_H
#define VKRENDERER_HANDLE_VECTOR_ITEM_H

template<typename ItemType>
class HandleVectorItem final {
private:
    alignas(ItemType) char data [sizeof(ItemType)] = {};
public:
    explicit HandleVectorItem(ItemType&& item);
    template<typename ...Args>
    explicit HandleVectorItem(Args... args);

    HandleVectorItem(const HandleVectorItem&)               = default;
    HandleVectorItem& operator=(const HandleVectorItem&)    = default;

public:
    ItemType& get();
    void cleanUp();
};

template<typename ItemType>
ItemType& HandleVectorItem<ItemType>::get() {
    return reinterpret_cast<ItemType&>(data);
}

template<typename ItemType>
void HandleVectorItem<ItemType>::cleanUp() {
    ItemType& item = get();
    item.~ItemType();
}

template<typename ItemType>
template<typename... Args>
HandleVectorItem<ItemType>::HandleVectorItem(Args... args) {
    void* memory = data;
    new (memory) ItemType(std::forward<Args>(args)...);
}

template<typename ItemType>
HandleVectorItem<ItemType>::HandleVectorItem(ItemType&& item) {
    void* memory = data;
    new (memory) ItemType(item);
}


#endif //VKRENDERER_HANDLE_VECTOR_ITEM_H
