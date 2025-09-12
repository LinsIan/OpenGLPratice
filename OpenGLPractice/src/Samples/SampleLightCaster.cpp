#include "SampleLightCaster.h"
#include "Cube.h"

namespace Sample
{
    SampleLightCaster::SampleLightCaster()
    {
        camera = std::make_unique<Camera>(CameraType::ORTHOGRAPHIC, 960, 540);

        DirLightProperties dirLightProperties;
        dirLightProperties.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
        dirLightProperties.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        dirLightProperties.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        dirLightProperties.specular = glm::vec3(1.0f, 1.0f, 1.0f);

        dirLight = std::make_unique<Light<DirLightProperties>>(LightType::DIRECTIONAL, dirLightProperties);

        auto cubeMaterial = std::make_shared<Material>("res/shaders/LightCaster.shader");
        cubeMaterial->AddTexture("res/textures/container2.png", 0, "material.diffuse");
        cubeMaterial->AddTexture("res/textures/container2_specular.png", 1, "material.specular");
        cubeMaterial->BindTextures();
        cubeMaterial->SetMaterialShininess(64.0f);

        cube = std::make_unique<GameObject>(std::make_shared<Model::Cube>(1.0f, 1.0f, 1.0f), cubeMaterial);
    }
/*
�����~�{?�ݪO C_Chat����ڭ��p����T
��^�ݪO
�@��dsa3717 (FishCA)
�ݪOC_Chat
���DRe: [Vtub] anycolor�]���]����F�^
�ɶ�Fri Sep 12 15:32:19 2025

https://finance.yahoo.co.jp/quote/5032.T

https://i.imgur.com/WdFP14m.jpeg


�]�����}��anycolor�ѻ��l��
�j�դW����6260
�i��D��2022.10.27�����v���I6895

�t�~�Y�N��10/9���~��???????????
�ثe�q�\�n���Ƥw�F��963,900


�� �ޭz�msteven96414 (�~�~�~�~�~)�n���ʨ�
: https://ssl4.eir-parts.net/doc/5032/tdnet/2685870/00.pdf
: ���I��z
: 1.�禬
: ?�W���G157��6800�E?�]�e�~�P����+112.1%�^
: ?�~�Q�q�G70��300�E?�]�P+157.6%�^
: ?�`�Q�q�G69��9800�E?�]�P+158.6%�^
: �§Q�q�G48��8400�E?�]�P+159.9%�^
: 2.
: �򤧫e���]���g���@��
: �w�p�C�~�~��X10~15%���s�H
: 3.�X�D�~�קO���q�^�m
: http://i.imgur.com/ouzb4mX.jpg

: 4.vtuber�禬�^�m
: �e25�W�@�ӤH�����^�m2%
: 26~50�W�@�ӤH�����^�m0.6%
: 51~100�W�@�ӤH�����^�m0.2%
: 5.�֦�anycolor ID�]�x��ө��b���^���H
: �k��71% �k��20%
: �~��20~29���e��̤j�A57%
: �ѤU���ۤv�ݧa
: -----
: Sent from JPTT on my Samsung SM-S9180.





--
�� �o�H��: �����~�{(ptt.cc), �Ӧ�: 42.79.21.237 (�O�W)
�� �峹���}: https://www.ptt.cc/bbs/C_Chat/M.1757662341.A.A8B.html
�� murderer2013: ���[�t�@���٦b��� 09/12 15:32
�� NekomataOkay: Cover����٦b2000 �b�a�W�� 09/12 15:33
�� ayubabbit: �i�SĹ 09/12 15:33
�� P2: �A�P���h�� 09/12 15:33
�� Cromwell2000: ���[ 09/12 15:33
�� Y1999: �t�~�@��O�b���H�i�������|�A�d�� 09/12 15:34
�� loverxa: ���w 09/12 15:35
�� lyt5566: ���w 09/12 15:36
�� greg90326: �A�̬O�b���|����= = 09/12 15:38
�� Augustus5: ��A�@�\�@�_�ܷ|�� 09/12 15:39
�� tsairay: �����������q�ɥN�٨S���,�A�U���٭n�A���� 09/12 15:39
�� guogu: ���w 09/12 15:40
�� tetsu327: ����U���n �Ѳ��Ȩ칡 09/12 15:40
�� SuiseiTrain: Ĺ�¤F �i�SĹ 09/12 15:41
�� a36772004: 4�Ӧb�P���ݪѻ� �b�ѻ��ݦP�� �n�� 09/12 15:43
�� FAQayame: https://i.imgur.com/7cRb3kv.jpeg 09/12 15:43

�� FAQayame: ���Q3�����F== 09/12 15:43
�� ntr203: ���[������@ �s�q�F����ɶ^ 09/12 15:44
�� KUSURI: �A���i�U���� �i���A�����o�@�� 09/12 15:44
�� pickchu22001: ���⪺�O����@���H 09/12 15:44
�� Y1999: �A���L�U����A�L���A�жU�٦bú 09/12 15:45
�� a20351: �ѻ��ҩ��֤~�O���b���T���D���W 09/12 15:45
�� shasen1236: �����H�Ȧh�֧a�A���p�G�h�@�I�����H��W�A���q�ѻ� 09/12 15:46
�� shasen1236: ���I�]�L�ҿ� 09/12 15:46
�� CYHyen: �L�̥��ȬO�h�ָ�h�֡H 09/12 15:47
�� wrh810701: ��ı�o �i������ԳN �|���[��ı�o��LIVER���Z������� 09/12 15:48
�� wrh810701: �a�A�A���������ب�U�H�T�U�H�x ��i��1000-2000�H�x 09/12 15:48
�� tk13os: �i�O���Ѳ��� 09/12 15:49
�� wrh810701: �֩w�O�H����֨���������[�����ʪ� 09/12 15:49
�� seer2525: �ѻ������H����h�ֿ����������Y�H 09/12 15:50
�N Akatsuki1006: �� ���ɦP������ԣ�� �m�i�{�u�_�ӦP���H�K10�X�U 09/12 15:50
�� Akatsuki1006: �_�� �ѻ���Ĺ�o�~�~�s 09/12 15:50
�� wrh810701: ���Q���ʨ쪺�[�� �@�N�������Ҥ@�w����� 09/12 15:50
�� RWmeat: google�d�� 09/12 15:50
�� RWmeat: cover 1350����� 09/12 15:50
�� RWmeat: anycolor  3820����� 09/12 15:50
�� wrh810701: ���C�Ӧ~���}�@�������M�n�A���iV��~��600-1000�U 09/12 15:51
�� CYHyen: �ҥH�T��]�t���h�T�� 09/12 15:51
�� wrh810701: �n�F�A���D�|�L�o�ܵh�W�ά����U�h�ܡH 09/12 15:52
�� victoryman: �m�i���h���i��ѥ_ 09/12 15:52
�� charlietk3: �ݤU�Aanycolor�I����D�O�ְ� 09/12 15:53
�� zmcef: �S����F 09/12 15:54
�� bnn: ��i�ѪF�ȿ��椺�� �S��f 09/12 15:54
�� seer2525: �u���O���ηQ���٭n���s�٨��� ��V���Ȥ��N��iV���� 09/12 15:54
�� steven96414: ���Q���ʨ쪺�[������e��������ܨ��۫H�[���u���� 09/12 15:55
�� steven96414: ��ƭӤH�դ@�w���ȧa�A�쩳����z��XDD 09/12 15:55
�� treeson: �A�i�⭿��V�ٯ�~�X�⭿�H�W���b�Q�A���U���H�����D�h 09/12 15:55
�� treeson: ���� 09/12 15:55
�� steven96414: �A���p���ƾڤ����S���������p�N�n 09/12 15:57
�� fairymomo: ���ް� ��������Ĺ�� 09/12 15:57
�� treeson: �{�u�����������۷�i�ѪF�A�L�|���^���UV�����ȿ� 09/12 15:57
�� Augustus5: �{�b�٦b�iV���Ȫ��N�~��˺ΧaXD 09/12 15:57
�� wrh810701: �C���[���@�N�᪺�������ҭi�@�w�O��������� 09/12 15:59
�� wrh810701: ���M�N���|�P���q�\�x���`���q��̮t���h�F 09/12 15:59
�� luna2000sea: �ݤ��쨮���O 09/12 16:00
�� SAsong319: �쩳�b������A�C���[����liver���b�餺�A�Z���n��� 09/12 16:00
�� SAsong319: ���� 09/12 16:00
�� wrh810701: �M�ᤣ�λ��ӤH�� �A�ݫeC�����k���N���D�F 09/12 16:00
�� wrh810701: ��᭱�[������20-30�H�ڬݦo�L�o�ٮ����� 09/12 16:01
�� uligaga: �����q�]�S�߿��a �N������� �@�Ӥ��q�j�Ȥ@�Ӥ��q�p�� 09/12 16:01
�� uligaga:  �����N�ϹL�� �զ�����t�S�h�� �Q��⭿�t �H�Ƥ]�O�� 09/12 16:01
�� uligaga: ���t 09/12 16:01
�� seer2525: ���򤣷|�̷|�۷Q�O�H�a�����^V �ۤv�a�̦�� 09/12 16:01
�� XUEcZ: �ҥH��V�ள��h�ְ� �쩳����~�O��B��XD 09/12 16:02
�� dieorrun: �Ȥ���h�N���O���^V ��˳������� 09/12 16:03
�� MoonSkyFish: ��������V�e5%���q�o�ؼƦr �i�n���S�� 09/12 16:03
�� dragon803: ���䪺�禬�W���t���h�� ��~�v�򦬯q�t�Z���ӬO�ݥL 09/12 16:03
�� dragon803: �̫���ꪺ�a 09/12 16:03
�� wrh810701: �c==�ި����N���F..�e25�@�H2% 09/12 16:03
�� wrh810701: �M���ı�o���κ�V����h�ְ� ���S���~�򰵤~�O�u�� 09/12 16:04
�� KUSURI: �q���q���ӻ��������I�ܭ��n �ӭi���_�����w�t�W�[�s�H 09/12 16:04
�� KUSURI:  ���N�O���_�a�b���o�Ӹg���h ���C�L�̷l�����@�H 09/12 16:04
�� KUSURI: ���v�T ������{���}�e��������_�� �w�g�Ҽ{�즳�H���}�] 09/12 16:04
�� KUSURI: �����۵M�s���N�¡^���᪺���k�i������� 09/12 16:04
�� Augustus5: �o�@��~�N����LIVE���ʳ����ܦh�s�H���|�A�]���H��� 09/12 16:05
�� dieorrun: �A�ݨ�ۤv���q�b�Q�� ���D�|ı�o�O�ۤv�����h? 09/12 16:05
�� Augustus5: �C���Ѧ������y�n���A�ڤ]�����D�O���^�b�� 09/12 16:05
�� treeson: �������������~��6000�U�ϰڡA�i�u������V��]��negligi 09/12 16:06
�� treeson: ble 09/12 16:06
�� treeson: ���M�O�u���A������V�����X���~�O���T�g��覡 09/12 16:07
�� charlietk3: �P�仡���^�ϦӤ������i�a 09/12 16:07
�� MoonSkyFish: ���Υ��ܷR���� �A������(�ڽ��l)��F�ʶR�a�\�� 09/12 16:07
�� uligaga: ��a�禬�򥻤@�� ��~�Q�q�v15%��35%���t�Z �M����嵦 09/12 16:07
�� uligaga: ���T��O�������I����k ����~�ӻ���í�� �����H�C�� 09/12 16:07
�� uligaga: �A���`���L 09/12 16:07
�� westgatepark: ���i�OP�� �@���O�� �����o�ˤ�]�O���Ӥ��� 09/12 16:08
�� a36772004: �O�o���O�H�e�N�Q�׹L "��V�Ȥ����~���|���~"�o���D 09/12 16:13
�� seer2525: yagoo�b�ѪF�|�]���L���ȿ����Y�P�u�����q��5% �o��O 09/12 16:14
�� seer2525: �@��negligible�ܡH 09/12 16:14
�� ASAKU581: 1�Ӧ�5%�N�ܥi�ȤF�A�A�ݹL�h�@�~�����F�X��5% 09/12 16:15
�� a125g: �ѻ��T���� 09/12 16:16
�� antatachi: �@�ӽ�PRM�L���F �Q�q�o���ӶˤF 09/12 16:17
�� a36772004: �p�G�s��������negligible ����L...?! 09/12 16:18
�� seer2525: �u��5%�Oyagoo���� ��ı�o5%�]�Z�h���� ���L���O���ȿ� 09/12 16:19
�� seer2525: �� ��L���O����5% 09/12 16:19
�� sicer: ��d�����L���e���@���D�D���n�����J�N�i�H���L�@�~������ 09/12 16:19
�� sicer: �����A�u��@�����n�N�i�H�@�~���μ��A����L�g�䦳���S�� 09/12 16:19
�� sicer: �[�W�h���藍�໡�O���ȧa 09/12 16:19
�� dsa3717: ����L���F�Acover�O�ۤv�M���� 09/12 16:20
����|�۰ʧ�s�A�÷|�۰ʱ���
�������w�̥x�W�������e���ųW�w�B�z�C���ϰ쬰����šA�����Q�K���̤��o�s���C
*/
    SampleLightCaster::~SampleLightCaster()
    {
    }

    void SampleLightCaster::OnUpdate(float deltaTime)
    {
    }

    void SampleLightCaster::OnRender()
    {
        dirLight->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
        cube->OnRender(camera->GetProjectionMatrix(), camera->GetViewMatrix());
    }

    void SampleLightCaster::OnImguiRender()
    {
    }
}
