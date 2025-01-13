#ifndef TESTS_ATOMICENTITY_H
#define TESTS_ATOMICENTITY_H

class AtomicEntity {
    bool ScalarEntity::addElement(BaseEntity *element) {
        Logger::log("Can't add child entity to atomic value");
        return false;
    }
};

#endif //TESTS_ATOMICENTITY_H
