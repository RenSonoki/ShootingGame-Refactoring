#pragma once
#include <random>

// C++11以降の標準ライブラリを使用して乱数を生成するクラス
// NOTE: 従来の rand() 関数はマルチスレッド環境では安全でなく非推奨のため
class Random
{
private:
    // メルセンヌ・ツイスター法による乱数生成エンジン
    static std::mt19937 engine;

public:
    // 初期化
    static void Init()
    {
        // 現在時刻をシードとしてエンジンを初期化
        std::random_device rd;
        engine.seed(rd());
    }

    // 指定範囲の整数を生成
    static int GetInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine);
    }

    // 指定範囲の浮動小数点数を生成
    static float GetFloat(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(engine);
    }
};

// 静的メンバ変数の実体を定義 (Random.cpp に記述)
// std::mt19937 Random::engine;