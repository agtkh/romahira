# romahira

A command-line tool that converts Romaji (Roman alphabet) to Hiragana.

## Features

- Converts standard Romaji input to Hiragana
- Supports both command-line arguments and stdin input
- Handles various Romaji conventions:
  - Basic syllables: `ka` → か, `shi` → し, `tsu` → つ, `fu` → ふ
  - Contracted sounds (yōon): `kya` → きゃ, `sha` → しゃ, `cho` → ちょ
  - Double consonants (sokuon): `kk`, `tt`, `ss`, `pp` → っ
  - Syllabic n (hatsuon): `n`, `nn` → ん, `mb`/`mp` → んb/んp

## Installation

### Build from source

```bash
git clone https://github.com/your-username/romahira.git
cd romahira
make
```

### Install to system

```bash
sudo make install
```

This installs the binary to `/usr/local/bin/`.

## Usage

### Command-line argument

```bash
romahira "konnichiwa"
# Output: こんにちわ

romahira "toukyou" "oosaka"
# Output: とうきょう おおさか
```

### Standard input

```bash
echo "arigatou" | romahira
# Output: ありがとう
```

```bash
romahira << EOF
ohayou
sayounara
EOF
# Output:
# おはよう
# さようなら
```

### Interactive mode

```bash
romahira
konnichiwa
# Output: こんにちわ
```

Press `Ctrl+D` to exit.

## Conversion Table

| Romaji | Hiragana | Romaji | Hiragana |
|--------|----------|--------|----------|
| a i u e o | あ い う え お | | |
| ka ki ku ke ko | か き く け こ | ga gi gu ge go | が ぎ ぐ げ ご |
| sa si/shi su se so | さ し す せ そ | za zi zu ze zo | ざ じ ず ぜ ぞ |
| ta ti/chi tu/tsu te to | た ち つ て と | da di du de do | だ ぢ づ で ど |
| na ni nu ne no | な に ぬ ね の | | |
| ha hi hu/fu he ho | は ひ ふ へ ほ | ba bi bu be bo | ば び ぶ べ ぼ |
| ma mi mu me mo | ま み む め も | pa pi pu pe po | ぱ ぴ ぷ ぺ ぽ |
| ya yu yo | や ゆ よ | | |
| ra ri ru re ro | ら り る れ ろ | | |
| wa wo | わ を | n/nn | ん |

### Contracted Sounds (Yōon)

| Romaji | Hiragana | Romaji | Hiragana |
|--------|----------|--------|----------|
| kya kyu kyo | きゃ きゅ きょ | gya gyu gyo | ぎゃ ぎゅ ぎょ |
| sha shu sho | しゃ しゅ しょ | ja ju jo | じゃ じゅ じょ |
| cha chu cho | ちゃ ちゅ ちょ | | |
| nya nyu nyo | にゃ にゅ にょ | | |
| hya hyu hyo | ひゃ ひゅ ひょ | bya byu byo | びゃ びゅ びょ |
| mya myu myo | みゃ みゅ みょ | pya pyu pyo | ぴゃ ぴゅ ぴょ |
| rya ryu ryo | りゃ りゅ りょ | | |

### Double Consonants (Sokuon)

Double consonants are converted to っ followed by the syllable:

- `kk` → っk (e.g., `kakko` → かっこ)
- `ss` → っs (e.g., `zasshi` → ざっし)
- `tt` → っt (e.g., `chotto` → ちょっと)
- `pp` → っp (e.g., `nippon` → にっぽん)

### Syllabic N (Hatsuon)

The syllabic n (ん) is produced by:

- `nn` → ん
- `n` before a consonant (except y) → ん (e.g., `shimbashi` → しんばし)
- `m` before b, m, p → ん (e.g., `ganbatte` → がんばって)

## Author

K.Agata

## License

MIT License
