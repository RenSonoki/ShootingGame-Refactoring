#define NOMINMAX
#include <windows.h>
#include <DxLib.h>

#include "Game.h"
#include "VirtualScreenManager.h"
#include "Random.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // ���O�o�͖�����
    SetOutApplicationLogValidFlag(FALSE);

    // ���z��ʃT�C�Y
    const int VIRTUAL_WIDTH = 1280;
    const int VIRTUAL_HEIGHT = 720;

    // �E�B���h�E���[�h�ɐݒ�
    ChangeWindowMode(TRUE);

    // DxLib�̏������Ɖ�ʐݒ�
    SetGraphMode(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, 32);
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    // 3D�`��̂��߂̐ݒ�
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    SetCameraNearFar(0.01f, 1000.0f);

    // �`�����o�b�N�o�b�t�@�ɐݒ�
    SetDrawScreen(DX_SCREEN_BACK);

    // --- �e�V���O���g���}�l�[�W���̏����� ---

    // ���z��ʏ����� (GetInstance() ���o�R���ČĂяo��)
    // NOTE: �w�i�F�͂����Ŏw��BWinMain����SetBackgroundColor�͕s�v�B
    VirtualScreenManager::GetInstance().Init(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

    // �����G���W���̏�����
    // NOTE: GetInstance()�����߂ČĂ΂ꂽ���ɃR���X�g���N�^������A�V�[�h���ݒ肳���
    Random::GetInstance();

    // Game�C���X�^���X����
    Game game;

    // ���C�����[�v
    LONGLONG prevTime = GetNowHiPerformanceCount();
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // DeltaTime�̌v�Z
        LONGLONG currentTime = GetNowHiPerformanceCount();
        float deltaTime = (currentTime - prevTime) / 1000000.0f;
        prevTime = currentTime;

        // --- �`�揈�� ---
        // �`��̊J�n����I���܂ł�VirtualScreenManager�ɔC����
        VirtualScreenManager::GetInstance().BeginDraw();

        // �Q�[���̍X�V�ƕ`��
        game.Update(deltaTime);
        game.Draw();

        // ���z��ʂ̓��e������ʂɓ]��
        VirtualScreenManager::GetInstance().EndDraw();

        // ����ʂ̓��e���f�B�X�v���C�ɔ��f
        ScreenFlip();
    }

    DxLib_End();
    return 0;
}