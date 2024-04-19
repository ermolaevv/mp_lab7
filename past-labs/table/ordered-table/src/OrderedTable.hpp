template<class Key, class Value>
Value* OrderedTable<Key, Value>::Find(Key key)
{
    int low = 0;
    int high = static_cast<int>(this->data.size() - 1);

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (this->data[mid].key == key) {
            return &this->data[mid].value;
        }
        if (this->data[mid].key < key) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    throw std::runtime_error("Key not found in the table.");
}

template<class Key, class Value>
void OrderedTable<Key, Value>::Insert(Key key, Value value)
{
    try {
        Value* existingValue = Find(key);
        *existingValue = value;
    }
    catch (const std::runtime_error&) {
        auto it = std::lower_bound(this->data.begin(), this->data.end(), key, [](const auto& record, const Key& key) {
            return record.key < key;
            });
        this->data.insert(it, { key, value });
    }
}

template<class Key, class Value>
void OrderedTable<Key, Value>::Delete(Key key)
{
    auto it = std::lower_bound(this->data.begin(), this->data.end(), key, [](const auto& record, const Key& key) {
        return record.key < key;
        });
    if (it != this->data.end() && it->key == key) {
        // erase удаляет и сдвигает
        this->data.erase(it);
    }
    else {
        throw std::runtime_error("Key not found in the table.");
    }
}
