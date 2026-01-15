#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    const char *romaji;
    const char *hiragana;
} RomajiEntry;

static const RomajiEntry table[] = {
    // 拗音 (3文字)
    {"kya", "きゃ"}, {"kyu", "きゅ"}, {"kyo", "きょ"},
    {"sha", "しゃ"}, {"shu", "しゅ"}, {"sho", "しょ"},
    {"cha", "ちゃ"}, {"chu", "ちゅ"}, {"cho", "ちょ"},
    {"nya", "にゃ"}, {"nyu", "にゅ"}, {"nyo", "にょ"},
    {"hya", "ひゃ"}, {"hyu", "ひゅ"}, {"hyo", "ひょ"},
    {"mya", "みゃ"}, {"myu", "みゅ"}, {"myo", "みょ"},
    {"rya", "りゃ"}, {"ryu", "りゅ"}, {"ryo", "りょ"},
    {"gya", "ぎゃ"}, {"gyu", "ぎゅ"}, {"gyo", "ぎょ"},
    {"ja", "じゃ"}, {"ji", "じ"}, {"ju", "じゅ"}, {"je", "じぇ"}, {"jo", "じょ"},
    {"jya", "じゃ"}, {"jyu", "じゅ"}, {"jyo", "じょ"},
    {"bya", "びゃ"}, {"byu", "びゅ"}, {"byo", "びょ"},
    {"pya", "ぴゃ"}, {"pyu", "ぴゅ"}, {"pyo", "ぴょ"},
    {"tya", "ちゃ"}, {"tyu", "ちゅ"}, {"tyo", "ちょ"},
    {"dya", "ぢゃ"}, {"dyu", "ぢゅ"}, {"dyo", "ぢょ"},
    {"shi", "し"}, {"chi", "ち"}, {"tsu", "つ"}, {"thi", "てぃ"},

    // 基本 (2文字)
    {"ka", "か"}, {"ki", "き"}, {"ku", "く"}, {"ke", "け"}, {"ko", "こ"},
    {"sa", "さ"}, {"si", "し"}, {"su", "す"}, {"se", "せ"}, {"so", "そ"},
    {"ta", "た"}, {"ti", "ち"}, {"tu", "つ"}, {"te", "て"}, {"to", "と"},
    {"na", "な"}, {"ni", "に"}, {"nu", "ぬ"}, {"ne", "ね"}, {"no", "の"},
    {"ha", "は"}, {"hi", "ひ"}, {"hu", "ふ"}, {"he", "へ"}, {"ho", "ほ"},
    {"ma", "ま"}, {"mi", "み"}, {"mu", "む"}, {"me", "め"}, {"mo", "も"},
    {"ya", "や"}, {"yu", "ゆ"}, {"yo", "よ"},
    {"ra", "ら"}, {"ri", "り"}, {"ru", "る"}, {"re", "れ"}, {"ro", "ろ"},
    {"wa", "わ"}, {"wi", "ゐ"}, {"we", "ゑ"}, {"wo", "を"},
    {"nn", "ん"},
    {"ga", "が"}, {"gi", "ぎ"}, {"gu", "ぐ"}, {"ge", "げ"}, {"go", "ご"},
    {"za", "ざ"}, {"zi", "じ"}, {"zu", "ず"}, {"ze", "ぜ"}, {"zo", "ぞ"},
    {"da", "だ"}, {"di", "ぢ"}, {"du", "づ"}, {"de", "で"}, {"do", "ど"},
    {"ba", "ば"}, {"bi", "び"}, {"bu", "ぶ"}, {"be", "べ"}, {"bo", "ぼ"},
    {"pa", "ぱ"}, {"pi", "ぴ"}, {"pu", "ぷ"}, {"pe", "ぺ"}, {"po", "ぽ"},
    {"fa", "ふぁ"}, {"fi", "ふぃ"}, {"fu", "ふ"}, {"fe", "ふぇ"}, {"fo", "ふぉ"},
    {"la", "ぁ"}, {"li", "ぃ"}, {"lu", "ぅ"}, {"le", "ぇ"}, {"lo", "ぉ"},
    {"xa", "ぁ"}, {"xi", "ぃ"}, {"xu", "ぅ"}, {"xe", "ぇ"}, {"xo", "ぉ"},
    {"va", "ゔぁ"}, {"vi", "ゔぃ"}, {"vu", "ゔ"}, {"ve", "ゔぇ"}, {"vo", "ゔぉ"},

    // 母音 (1文字)
    {"a", "あ"}, {"i", "い"}, {"u", "う"}, {"e", "え"}, {"o", "お"},
    {"n", "ん"},

    {NULL, NULL}
};

static int is_consonant(char c) {
    c = tolower(c);
    return c != 'a' && c != 'i' && c != 'u' && c != 'e' && c != 'o' &&
           c != 'n' && isalpha(c);
}

static int is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o';
}

static void convert(const char *input, FILE *out) {
    size_t len = strlen(input);
    size_t i = 0;

    while (i < len) {
        char lower[4];
        int matched = 0;

        // 撥音: m + b/m/p の場合は「ん」
        if (tolower(input[i]) == 'm' && i + 1 < len) {
            char next = tolower(input[i + 1]);
            if (next == 'b' || next == 'm' || next == 'p') {
                fprintf(out, "ん");
                i++;
                continue;
            }
        }

        // 撥音: n + 子音 (y以外) の場合は「ん」
        // ただし nn + 母音 の場合は最初の n だけ「ん」にする
        if (tolower(input[i]) == 'n' && i + 1 < len) {
            char next = tolower(input[i + 1]);
            // nn + 母音: 最初のnを「ん」として、残りのn+母音は次で処理
            if (next == 'n' && i + 2 < len && is_vowel(tolower(input[i + 2]))) {
                fprintf(out, "ん");
                i++;
                continue;
            }
            // n + 子音 (n, y以外)
            if (!is_vowel(next) && next != 'y' && next != 'n' && isalpha(next)) {
                fprintf(out, "ん");
                i++;
                continue;
            }
        }

        // 促音チェック: 同じ子音が連続する場合 (nn以外)
        if (i + 1 < len && is_consonant(input[i]) &&
            tolower(input[i]) == tolower(input[i + 1]) &&
            tolower(input[i]) != 'n') {
            fprintf(out, "っ");
            i++;
            continue;
        }

        // 3文字マッチを試行
        if (i + 2 < len) {
            for (int j = 0; j < 3; j++) {
                lower[j] = tolower(input[i + j]);
            }
            lower[3] = '\0';

            for (const RomajiEntry *e = table; e->romaji != NULL; e++) {
                if (strlen(e->romaji) == 3 && strcmp(lower, e->romaji) == 0) {
                    fprintf(out, "%s", e->hiragana);
                    i += 3;
                    matched = 1;
                    break;
                }
            }
        }

        // 2文字マッチを試行
        if (!matched && i + 1 < len) {
            for (int j = 0; j < 2; j++) {
                lower[j] = tolower(input[i + j]);
            }
            lower[2] = '\0';

            for (const RomajiEntry *e = table; e->romaji != NULL; e++) {
                if (strlen(e->romaji) == 2 && strcmp(lower, e->romaji) == 0) {
                    fprintf(out, "%s", e->hiragana);
                    i += 2;
                    matched = 1;
                    break;
                }
            }
        }

        // 1文字マッチを試行 (母音, n)
        if (!matched) {
            lower[0] = tolower(input[i]);
            lower[1] = '\0';

            // 'n' の特殊処理: 次が母音やyでない場合のみ「ん」に変換
            if (lower[0] == 'n') {
                if (i + 1 >= len ||
                    (tolower(input[i + 1]) != 'a' &&
                     tolower(input[i + 1]) != 'i' &&
                     tolower(input[i + 1]) != 'u' &&
                     tolower(input[i + 1]) != 'e' &&
                     tolower(input[i + 1]) != 'o' &&
                     tolower(input[i + 1]) != 'y')) {
                    fprintf(out, "ん");
                    i++;
                    matched = 1;
                }
            }

            if (!matched) {
                for (const RomajiEntry *e = table; e->romaji != NULL; e++) {
                    if (strlen(e->romaji) == 1 && strcmp(lower, e->romaji) == 0) {
                        fprintf(out, "%s", e->hiragana);
                        i++;
                        matched = 1;
                        break;
                    }
                }
            }
        }

        // マッチしない場合はそのまま出力
        if (!matched) {
            fputc(input[i], out);
            i++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        // コマンドライン引数から変換
        for (int i = 1; i < argc; i++) {
            convert(argv[i], stdout);
            if (i < argc - 1) {
                printf(" ");
            }
        }
        printf("\n");
    } else {
        // 標準入力から変換
        char line[4096];
        while (fgets(line, sizeof(line), stdin) != NULL) {
            // 改行を削除
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }
            convert(line, stdout);
            printf("\n");
        }
    }

    return 0;
}
