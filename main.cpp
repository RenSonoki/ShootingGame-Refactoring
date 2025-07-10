#include <DxLib.h>
#include "Game.h"
#include "VirtualScreenManager.h"
#include "Random.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // ���O�o�͖�����
    SetOutApplicationLogValidFlag(FALSE);

    // ���z��ʃT�C�Y�i�Q�[���݌v�Œ�`�j
    // NOTE: �����I�ɐݒ�t�@�C���Ȃǂ���ǂݍ��߂�悤�ɂ���ƁA���_��ɂȂ�܂��B
    const int VIRTUAL_WIDTH = 1280;
    const int VIRTUAL_HEIGHT = 720;

    // �E�B���h�E���[�h�ɐݒ�
    ChangeWindowMode(TRUE);

    // DxLib�̏������Ɖ�ʐݒ�
    // NOTE: DxLib_Init�̑O�ɃE�B���h�E���[�h�Ȃǂ�ݒ肵�Ă����K�v������܂��B
    SetGraphMode(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, 32);
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    // 3D�`��̂��߂̐ݒ�
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    // �`�����o�b�N�o�b�t�@�ɐݒ�
    SetDrawScreen(DX_SCREEN_BACK);

    // �w�i�F
    SetBackgroundColor(0, 255, 255);

    // �J�����̃N���b�v�ʐݒ�
    SetCameraNearFar(0.01f, 1000.0f);

    // ���z��ʏ�����
    VirtualScreenManager::Init(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

    // �����G���W���̏�����
    Random::Init();

    // Game�C���X�^���X�����i�����Ń��\�[�X�Ǘ����V�[���������j
    Game game;

    // ���C�����[�v
    LONGLONG prevTime = GetNowHiPerformanceCount();
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        LONGLONG currentTime = GetNowHiPerformanceCount();
        float deltaTime = (currentTime - prevTime) / 1000000.0f; // �}�C�N���b��b�ɕϊ�
        prevTime = currentTime;

        VirtualScreenManager::BeginDraw();  // ���z��ʂɕ`��J�n

        // ��ʃN���A�iBeginDraw�̌�A�ʂ̕`��̑O�ɌĂԂ̂���ʓI�j
        ClearDrawScreen();

        game.Update(deltaTime);  // �Q�[�����W�b�N�X�V
        game.Draw();    // �Q�[���`��

        VirtualScreenManager::EndDraw();    // ���z��ʂ̓��e������ʂ�

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}