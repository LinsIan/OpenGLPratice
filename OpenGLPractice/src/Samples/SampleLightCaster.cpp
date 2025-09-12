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
批踢踢實業坊?看板 C_Chat關於我們聯絡資訊
返回看板
作者dsa3717 (FishCA)
看板C_Chat
標題Re: [Vtub] anycolor財報（賺爛了）
時間Fri Sep 12 15:32:19 2025

https://finance.yahoo.co.jp/quote/5032.T

https://i.imgur.com/WdFP14m.jpeg


財報公開後anycolor股價勁揚
強勢上漲到6260
可望挑戰2022.10.27的歷史高點6895

另外即將於10/9畢業的???????????
目前訂閱登錄數已達到963,900


※ 引述《steven96414 (居居居居居)》之銘言
: https://ssl4.eir-parts.net/doc/5032/tdnet/2685870/00.pdf
: 重點整理
: 1.營收
: ?上高：157億6800万?（前年同期比+112.1%）
: ?業利益：70億300万?（同+157.6%）
: ?常利益：69億9800万?（同+158.6%）
: 純利益：48億8400万?（同+159.9%）
: 2.
: 跟之前的財報寫的一樣
: 預計每年繼續出10~15%的新人
: 3.出道年度別收益貢獻
: http://i.imgur.com/ouzb4mX.jpg

: 4.vtuber營收貢獻
: 前25名一個人平均貢獻2%
: 26~50名一個人平均貢獻0.6%
: 51~100名一個人平均貢獻0.2%
: 5.擁有anycolor ID（官方商店帳號）的人
: 女性71% 男性20%
: 年齡20~29歲占比最大，57%
: 剩下的自己看吧
: -----
: Sent from JPTT on my Samsung SM-S9180.





--
※ 發信站: 批踢踢實業坊(ptt.cc), 來自: 42.79.21.237 (臺灣)
※ 文章網址: https://www.ptt.cc/bbs/C_Chat/M.1757662341.A.A8B.html
→ murderer2013: 反觀另一邊還在圓夢 09/12 15:32
推 NekomataOkay: Cover怎麼還在2000 在地上爬 09/12 15:33
推 ayubabbit: 虹又贏 09/12 15:33
推 P2: 你同接多少 09/12 15:33
推 Cromwell2000: 反觀 09/12 15:33
→ Y1999: 另外一邊是在給人進場的機會，寵粉 09/12 15:34
推 loverxa: 反歡 09/12 15:35
推 lyt5566: 反歡 09/12 15:36
推 greg90326: 你們是在反鸛什麼= = 09/12 15:38
推 Augustus5: 把你咖擺一起很會喔 09/12 15:39
→ tsairay: 齁的絲綢之歌時代還沒到來,你各位還要再等等 09/12 15:39
推 guogu: 及歡 09/12 15:40
推 tetsu327: 水餃下的好 股票賺到飽 09/12 15:40
推 SuiseiTrain: 贏麻了 虹又贏 09/12 15:41
推 a36772004: 4樓在同接問股價 在股價問同階 好喔 09/12 15:43
推 FAQayame: https://i.imgur.com/7cRb3kv.jpeg 09/12 15:43

→ FAQayame: 怎麼被3倍殺了== 09/12 15:43
推 ntr203: 反觀狗屎爛咖 連通靈都能暴跌 09/12 15:44
推 KUSURI: 你笑虹下水餃 虹笑你不懂這一行 09/12 15:44
推 pickchu22001: 黃色的是路邊一條？ 09/12 15:44
→ Y1999: 你笑他下水餃，他笑你房貸還在繳 09/12 15:45
推 a20351: 股價證明誰才是走在正確的道路上 09/12 15:45
推 shasen1236: 看藝人賺多少吧，錢如果多一點到藝人手上，公司股價 09/12 15:46
→ shasen1236: 少點也無所謂 09/12 15:46
推 CYHyen: 他們市值是多少跟多少？ 09/12 15:47
→ wrh810701: 我覺得 虹的水餃戰術 會讓觀眾覺得跟LIVER的距離比較近 09/12 15:48
→ wrh810701: 吧，你跟齁的那種兩萬人三萬人台 跟虹的1000-2000人台 09/12 15:48
推 tk13os: 虹是懂股票的 09/12 15:49
→ wrh810701: 肯定是人比較少那邊比較能跟觀眾互動的 09/12 15:49
推 seer2525: 股價跟藝人拿到多少錢有什麼關係？ 09/12 15:50
噓 Akatsuki1006: 唉 平時同接高有啥用 彩虹認真起來同接隨便10幾萬 09/12 15:50
→ Akatsuki1006: 起跳 股價還贏得嚇嚇叫 09/12 15:50
→ wrh810701: 有被互動到的觀眾 願意花錢的比例一定比較高 09/12 15:50
推 RWmeat: google查的 09/12 15:50
→ RWmeat: cover 1350億日圓 09/12 15:50
→ RWmeat: anycolor  3820億日圓 09/12 15:50
→ wrh810701: 齁每個年收破一億日幣當然好，但虹V算年收600-1000萬 09/12 15:51
推 CYHyen: 所以確實也差不多三倍 09/12 15:51
→ wrh810701: 好了，難道會過得很痛苦或活不下去嗎？ 09/12 15:52
推 victoryman: 彩虹鬥士不可能敗北 09/12 15:52
推 charlietk3: 問下，anycolor背後金主是誰啊 09/12 15:53
→ zmcef: 又賺爛了 09/12 15:54
→ bnn: 當虹股東賺錢斗內齁 沒毛病 09/12 15:54
推 seer2525: 真的是不用想酸還要拐彎抹角的 齁V很賺不代表虹V不賺 09/12 15:54
推 steven96414: 有被互動到的觀眾比較容易花錢的話那相信觀眾只有兩 09/12 15:55
→ steven96414: 位數個人勢一定最賺吧，到底什麼理論XDD 09/12 15:55
推 treeson: 你虹兩倍的V還能洗出兩倍以上的淨利，底下的人不知道多 09/12 15:55
→ treeson: 幸福 09/12 15:55
推 steven96414: 你不如說數據之間沒有直接關聯就好 09/12 15:57
推 fairymomo: 不管啦 齁哪次不贏麻 09/12 15:57
→ treeson: 認真說我齁粉但相當虹股東，他會壓榨底下V幫我賺錢 09/12 15:57
推 Augustus5: 現在還在虹V不賺的就繼續裝睡吧XD 09/12 15:57
→ wrh810701: 每個觀眾願意花的錢整體比例虹一定是比較高的啊 09/12 15:59
→ wrh810701: 不然就不會同接訂閱屌打總收益兩者差不多了 09/12 15:59
→ luna2000sea: 看不到車尾燈 09/12 16:00
推 SAsong319: 到底在講什麼，每個觀眾的liver都在體內，距離要怎麼 09/12 16:00
→ SAsong319: 不近 09/12 16:00
→ wrh810701: 然後不用說個人勢 你看前C洽之女不就知道了 09/12 16:00
→ wrh810701: 到後面觀眾平均20-30人我看她過得還挺滋潤的 09/12 16:01
推 uligaga: 齁公司也沒賠錢吧 就比較不賺 一個公司大賺一個公司小賺 09/12 16:01
→ uligaga:  成員就反過來 盈收兩邊差沒多少 利潤兩倍差 人數也是兩 09/12 16:01
→ uligaga: 倍差 09/12 16:01
推 seer2525: 什麼不會最會幻想別人家都壓榨V 自己家最佛心 09/12 16:01
推 XUEcZ: 所以說V能拿到多少啊 到底哪邊才是營運粉XD 09/12 16:02
→ dieorrun: 賺比較多就說是壓榨V 怎樣都有話講 09/12 16:03
推 MoonSkyFish: 齁有頂端V占5%收益這種數字 虹好像沒講 09/12 16:03
推 dragon803: 兩邊的營收上限差不多高 營業率跟收益差距應該是看他 09/12 16:03
→ dragon803: 們怎麼投資的吧 09/12 16:03
→ wrh810701: 呃==引言不就講了..前25一人2% 09/12 16:03
→ wrh810701: 然後我覺得不用管V拿到多少啦 有沒有繼續做才是真的 09/12 16:04
推 KUSURI: 從公司面來說分散風險很重要 而虹不斷維持定速增加新人 09/12 16:04
→ KUSURI:  其實就是不斷地在實踐這個經營原則 降低他們損失任一人 09/12 16:04
→ KUSURI: 的影響 跟維持現有陣容的策略比起來 已經考慮到有人離開（ 09/12 16:04
→ KUSURI: 成員自然新陳代謝）之後的做法可能比較實際 09/12 16:04
推 Augustus5: 這一兩年代言跟LIVE活動都給很多新人機會，也讓人氣較 09/12 16:05
→ dieorrun: 你看到自己公司淨利少 難道會覺得是自己領比較多? 09/12 16:05
→ Augustus5: 低的老成員輪流登場，我也不知道是壓榨在哪 09/12 16:05
推 treeson: 齁有公布平均年收6000萬羊啊，虹只有公布V對財報negligi 09/12 16:06
→ treeson: ble 09/12 16:06
→ treeson: 雖然是真的，狠狠對V重拳出擊才是正確經營方式 09/12 16:07
→ charlietk3: 與其說壓榨反而比較像放養吧 09/12 16:07
→ MoonSkyFish: 鬥蟲民很愛講的 你齁底邊(蘿蔔子)能東京買地蓋房 09/12 16:07
推 uligaga: 兩家營收基本一樣 營業利益率15%跟35%的差距 然後水餃策 09/12 16:07
→ uligaga: 略確實是分散風險的方法 對企業來說很穩健 受投資人青睞 09/12 16:07
→ uligaga: 再正常不過 09/12 16:07
→ westgatepark: 但虹是P股 咖不是啊 直接這樣比也是不太公平 09/12 16:08
→ a36772004: 記得不是以前就討論過 "讓V賺不夠才不會畢業"這話題 09/12 16:13
推 seer2525: yagoo在股東會也說過最賺錢的頭牌只佔公司的5% 這算是 09/12 16:14
→ seer2525: 一種negligible嗎？ 09/12 16:14
推 ASAKU581: 1個佔5%就很可怕了，你看過去一年齁走了幾個5% 09/12 16:15
推 a125g: 股價三倍殺 09/12 16:16
→ antatachi: 咖申請PRM過不了 利益這塊太傷了 09/12 16:17
→ a36772004: 如果連齁面都算negligible 那其他...?! 09/12 16:18
推 seer2525: 只佔5%是yagoo講的 我覺得5%也蠻多的啊 不過那是最賺錢 09/12 16:19
→ seer2525: 的 其他都是不到5% 09/12 16:19
推 sicer: 柴卡有說他之前有一期主題音聲的收入就可以讓他一年都不用 09/12 16:19
→ sicer: 直播，只賣一次音聲就可以一年不用播，那其他週邊有的沒的 09/12 16:19
→ sicer: 加上去絕對不能說是不賺吧 09/12 16:19
→ dsa3717: 什麼過不了，cover是自己撤掉的 09/12 16:20
推文會自動更新，並會自動捲動
本網站已依台灣網站內容分級規定處理。此區域為限制級，未滿十八歲者不得瀏覽。
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
