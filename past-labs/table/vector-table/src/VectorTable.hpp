template<class Key, class Value>
Value* VectorTable<Key, Value>::Find(Key key)
{
    auto it = std::find_if(data.begin(), data.end(), [key](const auto& record) { return record.key == key; });
    if (it != data.end()) {
        return &it->value;
    }
    throw std::runtime_error("Key not found in the table.");
}

template<class Key, class Value>
void VectorTable<Key, Value>::Insert(Key key, Value value)
{
    try {
        Value* existingValue = Find(key);
        *existingValue = value;
    }
    catch (const std::runtime_error&) {
        data.push_back({ key, value });
    }
}

template<class Key, class Value>
void VectorTable<Key, Value>::Delete(Key key) {
    auto it = std::find_if(data.begin(), data.end(), [key](const auto& record) { return record.key == key; });
    if (it != data.end()) {
        // Меняем с последним
        if (it != data.end() - 1) {
            std::swap(*it, data.back());
        }
        // Последний элемент удаляем
        data.pop_back();
    }
    else {
        throw std::runtime_error("Key not found in the table.");
    }
}

template<class Key, class Value>
bool VectorTable<Key, Value>::IsTabEnded(void) const noexcept
{
    return this->position >= data.size();
}

template<class Key, class Value>
size_t VectorTable<Key, Value>::GoNext(void) noexcept
{
    if (this->position < data.size()) {
        this->position++;
    }
    else {
        this->position = 0;
    }
    return this->position;
}

template<class Key, class Value>
Key VectorTable<Key, Value>::GetKey(void) const
{
    if (this->IsTabEnded()) {
        throw std::runtime_error("End of table reached.");
    }
    return data[this->position].key;
}

template<class Key, class Value>
Value* VectorTable<Key, Value>::GetValuePtr(void) const
{
    if (this->IsTabEnded()) {
        throw std::runtime_error("End of table reached.");
    }

    return &data[this->position].value;
}
