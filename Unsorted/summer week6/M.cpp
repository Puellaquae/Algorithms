#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

constexpr char TAO = 'P';
constexpr char SHA = 'K';
constexpr char SHAN = 'D';

constexpr char JUE_DOU = 'F';
constexpr char NAN_ZHU_RU_QING = 'N';
constexpr char WAN_JIAN_QI_FA = 'W';
constexpr char WU_XI_KE_JI = 'J';

constexpr char ZHU_GE_LIAN_NU = 'Z';

enum class PLAYER_TYPE {
    MP,
    ZP,
    FP
};

constexpr int MAX_LIFE = 4;
using namespace std;

class Game {
    vector<char> CardPool;
    bool gameover = false;
    string win;
    int main_pig_idx = 0;
    int player_cnt = 0;
    int anti_cnt = 0;
    bool inNanZhuRuQing = false;
    bool inWanJianQiFa = false;
    bool inFight = false;

    class Pig {
        PLAYER_TYPE role;
        int position;
        int life = MAX_LIFE;

        struct Card {
            char card;
            bool used = false;

            bool operator==(const Card &c) const {
                return card == c.card && used == c.used;
            }

            Card(const char c):
                card{c} {}
        };

        vector<Card> cards;
        Game *game;
        bool dead = false;
        bool equiped = false;
        bool usedKill = false;
        bool FPish = false;
        bool showedRole = false;
        bool isMP = false;
        bool isZP = false;
        bool isFP = false;
    public:
        friend Game;

        Pig(const PLAYER_TYPE type,
            const int pos,
            const char card1,
            const char card2,
            const char card3,
            const char card4,
            Game *game):
            role{type}, position{pos}, cards{card1, card2, card3, card4}, game{game} {
            if (type == PLAYER_TYPE::MP) {
                isMP = true;
            } else if (type == PLAYER_TYPE::ZP) {
                isZP = true;
            } else {
                isFP = true;
            }
        }

        void Action() {
            for (bool usecarded = true; usecarded;) {
                usecarded = false;
                for (auto &card : cards) {
                    if (card.used)
                        continue;
                    switch (card.card) {
                        case TAO: {
                            if (life < MAX_LIFE) {
                                card.used = true;
                                game->UseCard(position, TAO);
                                usecarded = true;
                            }
                            break;
                        }
                        case SHA: {
                            const int target = game->RequireKillTarget(position);
                            if (target != -1) {
                                card.used = true;
                                game->UseCard(position, SHA, target);
                                usecarded = true;
                            }
                            break;
                        }
                        case JUE_DOU: {
                            const int target = game->RequireFightTarget(position);
                            if (target != -1) {
                                card.used = true;
                                game->UseCard(position, JUE_DOU, target);
                                usecarded = true;
                            }
                            break;
                        }
                        case NAN_ZHU_RU_QING: {
                            card.used = true;
                            game->UseCard(position, NAN_ZHU_RU_QING);
                            usecarded = true;
                            break;
                        }
                        case WAN_JIAN_QI_FA: {
                            card.used = true;
                            game->UseCard(position, WAN_JIAN_QI_FA);
                            usecarded = true;
                            break;
                        }
                        case ZHU_GE_LIAN_NU: {
                            card.used = true;
                            game->UseCard(position, ZHU_GE_LIAN_NU);
                            usecarded = true;
                            break;
                        }
                        default: ;
                    }
                    if (usecarded) {
                        if (dead || game->gameover) {
                            return;
                        }
                        break;
                    }
                }
            }
        }

        bool RequireUseCard(const char card) {
            const auto it = find(cards.begin(), cards.end(), card);
            if (it == cards.end()) {
                return false;
            }
            it->used = true;
            game->PassiveUseCard(position, card);
            return true;
        }
    };

    vector<Pig> Players;

    void GiveCard(const int who, int cnt) {
        while (cnt--) {
            Players[who].cards.emplace_back(CardPool.back());
#ifdef _DEBUG
            printf("#%d Get %c\n", who, CardPool.back());
#endif

            if (CardPool.size() > 1)
                CardPool.pop_back();
        }
    }

    void NanZhuRuQing(const int who) {
        for (int i = 1; i < player_cnt; i++) {
            const int rpos = (i + who) % player_cnt;
            if (!Players[rpos].dead) {
                if (AskUseWuXieKeJi(who, rpos)) {
                    continue;
                }
                if (!Players[rpos].RequireUseCard(SHA)) {
                    MakeHurt(who, rpos);
                    if (gameover) {
                        return;
                    }
                    if (Players[rpos].isMP && !Players[who].showedRole) {
                        Players[who].FPish = true;
                    }
                }
            }
        }
    }

    void Died(const int who, const int becauseWho) {
#ifdef _DEBUG
        printf("#%d Died\n", who);
#endif

        auto &p = Players[who];
        p.dead = true;
        if (p.isMP) {
            win = "FP";
            gameover = true;
        } else if (p.isFP) {
            anti_cnt--;
            if (anti_cnt == 0) {
                win = "MP";
                gameover = true;
                return;
            }
            GiveCard(becauseWho, 3);
        } else if (Players[becauseWho].isMP && p.isZP) {
            Players[becauseWho].cards.clear();
            Players[becauseWho].equiped = false;
        }
    }

    bool AliveCheck(const int who) {
        return Players[who].life != 0 || Players[who].RequireUseCard(TAO);
    }

    void MakeHurt(const int who, const int toWho) {
        Players[toWho].life--;
#ifdef _DEBUG
        printf("#%d Hurted by #%d, #%d hp: %d\n", toWho, who, toWho, Players[toWho].life);
#endif

        if (!AliveCheck(toWho)) {
            Died(toWho, who);
        }
    }

    void Kill(const int who, const int toWho) {
        Players[who].showedRole = true;
        Players[who].FPish = false;
        Players[who].usedKill = true;
        if (!Players[toWho].RequireUseCard(SHAN)) {
            MakeHurt(who, toWho);
        }
    }

    void Fight(const int who, const int toWho) {
        Players[who].showedRole = true;
        Players[who].FPish = false;
        if (AskUseWuXieKeJi(who, toWho)) {
            return;
        }
        if (Players[who].isMP && Players[toWho].isZP) {
            MakeHurt(who, toWho);
            return;
        }
        while (true) {
            if (!Players[toWho].RequireUseCard(SHA)) {
                MakeHurt(who, toWho);
                break;
            }
            if (!Players[who].RequireUseCard(SHA)) {
                MakeHurt(toWho, who);
                break;
            }
        }
    }

    void WanJianQiFa(const int who) {
        for (int i = 1; i < player_cnt; i++) {
            const int rpos = (i + who) % player_cnt;
            if (!Players[rpos].dead) {
                if (AskUseWuXieKeJi(who, rpos)) {
                    continue;
                }
                if (!Players[rpos].RequireUseCard(SHAN)) {
                    MakeHurt(who, rpos);
                    if (gameover) {
                        return;
                    }
                    if (Players[rpos].isMP && !Players[who].showedRole) {
                        Players[who].FPish = true;
                    }
                }
            }
        }
    }

    void Cure(const int who) {
        Players[who].life++;
#ifdef _DEBUG
        printf("Cure #%d, hp %d\n", who, Players[who].life);
#endif
    }

    void UseCard(const int who, const char card, const int toWho = -1) {
#ifdef _DEBUG
        if (toWho != -1) {
            printf("#%d Use %c To #%d\n", who, card, toWho);
        } else {
            printf("#%d Use %c\n", who, card);
        }
#endif

        switch (card) {
            case TAO: {
                Cure(who);
                break;
            }
            case SHA: {
                if (!inNanZhuRuQing && !inFight) { Kill(who, toWho); }
                break;
            }
            case SHAN: {
                break;
            }
            case JUE_DOU: {
#ifdef _DEBUG
                printf("Fight Start\n");
#endif
                inFight = true;
                Fight(who, toWho);
                inFight = false;
#ifdef _DEBUG
                printf("Fight End\n");
#endif
                break;
            }
            case NAN_ZHU_RU_QING: {
#ifdef _DEBUG
                printf("NanZhuRuQind Start\n");
#endif
                inNanZhuRuQing = true;
                NanZhuRuQing(who);
                inNanZhuRuQing = false;
#ifdef _DEBUG
                printf("NanZhuRuQind End\n");
#endif
                break;
            }
            case WAN_JIAN_QI_FA: {
#ifdef _DEBUG
                printf("WanJianQiFa Start\n");
#endif
                inWanJianQiFa = true;
                WanJianQiFa(who);
                inWanJianQiFa = false;
#ifdef _DEBUG
                printf("WanJianQiFa End\n");
#endif
                break;
            }
            case WU_XI_KE_JI: {
                break;
            }
            case ZHU_GE_LIAN_NU: {
                Players[who].equiped = true;
                break;
            }
            default:
                break;
        }
    }

    void PassiveUseCard(const int who, const char card) {
#ifdef _DEBUG
        printf("#%d Use %c Passive\n", who, card);
#endif

        if (card == TAO) {
            Cure(who);
        }
    }

    int GetRightFirstAlivePig(const int fromWho) {
        for (int i = (fromWho + 1) % player_cnt; i != fromWho; i = (i + 1) % player_cnt) {
            if (Players[i].dead) {
                continue;
            }
            return i;
        }
        return -1;
    }

    int RequireKillTarget(const int who) {
        if (Players[who].usedKill && !Players[who].equiped) {
            return -1;
        }
        const int rpos = GetRightFirstAlivePig(who);
        if (Players[who].isMP) {
            if (Players[rpos].FPish || Players[rpos].isFP && Players[
                rpos].showedRole) {
                return rpos;
            }
        } else if (Players[who].isZP) {
            if (Players[rpos].isFP && Players[rpos].showedRole) {
                return rpos;
            }
        } else {
            if (!Players[rpos].isFP && Players[rpos].showedRole) {
                return rpos;
            }
        }
        return -1;
    }

    int RequireFightTarget(const int who) {
        if (Players[who].isMP) {
            for (int i = (who + 1) % player_cnt; i != who; i = (i + 1) % player_cnt) {
                if (Players[i].dead) {
                    continue;
                }
                if (Players[i].FPish || Players[i].isFP && Players[i].
                    showedRole) {
                    return i;
                }
            }
        } else if (Players[who].isZP) {
            for (int i = (who + 1) % player_cnt; i != who; i = (i + 1) % player_cnt) {
                if (Players[i].dead) {
                    continue;
                }
                if (Players[i].isFP && Players[i].showedRole) {
                    return i;
                }
            }
        } else {
            return main_pig_idx;
        }
        return -1;
    }

    bool AgainstAskUseWuXieKeJi(const int toWho) {
        auto &w = Players[toWho];
        for (int i = (toWho + 1) % player_cnt; i != toWho; i = (i + 1) % player_cnt) {
            if (Players[i].dead) {
                continue;
            }
            if (w.isMP && Players[i].isZP) {
                continue;
            }
            if (w.isZP && Players[i].isZP) {
                continue;
            }
            if (w.isFP && Players[i].isFP) {
                continue;
            }
            if (w.isZP && Players[i].isMP) {
                continue;
            }
            if (Players[i].RequireUseCard(WU_XI_KE_JI)) {
                Players[i].showedRole = true;
                return !AgainstAskUseWuXieKeJi(i);
            }
        }
        return false;
    }

    bool AskUseWuXieKeJi(const int startAskFrom, const int forWho) {
        if (!Players[forWho].showedRole) {
            return false;
        }
        auto &f = Players[forWho];
        bool flag = true;
        for (int i = startAskFrom; i != startAskFrom || flag; i = (i + 1) % player_cnt) {
            flag = false;
            if (Players[i].dead) {
                continue;
            }
            if (f.isMP && Players[i].isFP) {
                continue;
            }
            if (f.isZP && Players[i].isFP) {
                continue;
            }
            if (f.isFP && Players[i].isZP) {
                continue;
            }
            if (f.isFP && Players[i].isMP) {
                continue;
            }
            if (Players[i].RequireUseCard(WU_XI_KE_JI)) {
                Players[i].showedRole = true;
                return !AgainstAskUseWuXieKeJi(i);
            }
        }
        return false;
    }

public
:
    Game(const int playercnt, const int cardcnt):
        player_cnt{playercnt} {
        for (int i = 0; i < playercnt; i++) {
            string type, card1, card2, card3, card4;
            cin >> type >> card1 >> card2 >> card3 >> card4;
            if (type == "MP") {
                main_pig_idx = i;
            } else if (type == "FP") {
                anti_cnt++;
            }
            auto str2Type = [](const string &str) {
                if (str == "MP")
                    return PLAYER_TYPE::MP;
                if (str == "ZP")
                    return PLAYER_TYPE::ZP;
                return PLAYER_TYPE::FP;
            };
            Players.emplace_back(str2Type(type),
                                 i,
                                 card1[0],
                                 card2[0],
                                 card3[0],
                                 card4[0],
                                 this);
            Players[main_pig_idx].showedRole = true;
        }
        CardPool.resize(cardcnt);
        for (char &c : CardPool) {
            cin >> c;
        }
        reverse(CardPool.begin(), CardPool.end());
    }

#ifdef _DEBUG
    void ShowPlayerInf() {
        for (auto &&player : Players) {
            printf("P%d hp %d Card: ", player.position, player.life);
            for (auto &&card : player.cards) {
                if (!card.used) { printf("%c ", card.card); }
            }
            printf("\n");
        }
    }
#endif

    void Play() {
        if (anti_cnt == 0) {
            win = "MP";
            gameover = true;
            return;
        }
#ifdef _DEBUG
        int round = 0;
#endif

        while (true) {
#ifdef _DEBUG
            printf("\nRound %d\n", round++);
#endif

            for (auto &player : Players) {
                if (!player.dead) {
#ifdef _DEBUG
                    printf("\n#%d Turns\n", player.position);
                    ShowPlayerInf();
                    printf("\n");
                    system("pause");
#endif

                    GiveCard(player.position, 2);
                    player.Action();
                    player.usedKill = false;
                    if (gameover) {
                        return;
                    }
                }
            }
        }
    }

    void Account() {
        cout << win << endl;
        for (auto &&player : Players) {
            if (player.dead) {
                cout << "DEAD\n";
            } else {
                for (auto &&card : player.cards) {
                    if (!card.used) {
                        cout << card.card << " ";
                    }
                }
                cout << endl;
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Game game(n, m);
    game.Play();
    game.Account();
}
