#pragma once

// �Q�[���̏�Ԃ⃋�[�����Ǘ�����V���O���g��
class GameManager
{
public:
    // �B��̃C���X�^���X���擾
    static GameManager& GetInstance();

    // �V���O���g���Ȃ̂ŃR�s�[�ƃ��[�u�͋֎~
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    // --- �Q�[�����W�b�N ---
    void AddScore(int score);
    void Reset(); // �Q�[���J�n���ȂǂɌĂ΂��
    int GetScore() const;

private:
    // private�R���X�g���N�^�ŊO������̐������֎~
    GameManager() = default;

    int m_score = 0;
    // ����A�c�胉�C�t���Ȃǂ������ɒǉ����Ă���
    // int m_lives = 3;
};