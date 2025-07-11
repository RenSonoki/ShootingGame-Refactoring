#include "Random.h"
// Random.h で「宣言」された静的メンバー変数 engine の「定義」
// これにより、変数の実体がプログラム内に生成される
std::mt19937 Random::engine;