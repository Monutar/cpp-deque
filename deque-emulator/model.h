#pragma once

#include <string>
#include <deque>

using namespace std;
using namespace std::literals;

static deque<string> tea {
    "Чай Лунцзин"s,
    "Эрл Грей"s,
    "Сенча"s,
    "Пуэр"s,
    "Дарджилинг"s,
    "Ассам"s,
    "Матча"s,
    "Ганпаудер"s,
    "Оолонг"s,
    "Лапсанг Сушонг"s,
};

static deque<string> cakes {
    "Красный бархат"s,
    "Наполеон"s,
    "Медовик"s,
    "Тирамису"s,
    "Прага"s,
    "Чизкейк"s,
    "Захер"s,
    "Эстерхази"s,
    "Морковный торт"s,
    "Чёрный лес"s,
};


struct Model {
    using Deque = deque<string>;
    Deque items;
    Deque::iterator iterator = items.begin();
};

