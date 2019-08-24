#pragma once
#ifndef ECCR0013_ITEMGENERATE
#define ECCR0013_ITEMGENERATE

#include "itemgenerate_intfc.hpp"

namespace ECCR0013 {
    class ItemGenerate : public ItemGenerate_intfc {
    public:
        ItemGenerate(void) = delete;
        ItemGenerate(const ItemGenerate &) = delete;
        ItemGenerate operator= (const ItemGenerate &) = delete;

        ItemGenerate(ItemManager_intfc::ItemManagerHandle);
        ~ItemGenerate(void);

        ERI_Message Register(GenerateEventList const &);
        ERI_Message Execute(std::string const &);
        bool IsFinished(std::string const &);
        ERI_Messagequeue Update(float const &);
    private:
        class Impl;
        Impl *pimpl = nullptr;
    };
}
#endif // !ECCR0013_ITEMGENERATE
