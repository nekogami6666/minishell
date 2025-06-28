# minishell

42 Tokyo／AlmaLinux評価VM向けに開発した、Norm 準拠のミニシェル実装です。  
標準的なシェル機能（ビルトイン、リダイレクト、パイプ、環境変数展開など）を自前で実装し、C言語の基礎からプロセス・ファイル操作の理解を深めることを目的としています。

---

## 🌟 主な機能

- 🎉 **ビルトインコマンド**  
  - `echo` `cd` `pwd` `export` `unset` `env` `exit`
- 🔄 **リダイレクト**  
  - 出力の上書き `>`  
  - 出力の追記 `>>`  
  - 入力のリダイレクト `<`
- 🔗 **パイプ**  
  - 単一／複数コマンドのパイプ接続 `cmd1 | cmd2 | cmd3`
- 🔤 **環境変数展開**  
  - `$VAR`  
  - 特殊変数 `$$`（PID）、`$?`（直前コマンド終了ステータス）
- 📳 **シグナルハンドリング**  
  - Ctrl+C でプロンプト復帰、Ctrl+\ は無視
- 🛠 **Norm 準拠**  
  - 関数・ファイル 25 行以内  
  - インデント 4 スペース  
  - ファイル名・関数名は小文字＋アンダースコア

---

## 🛠️ 動作環境

- OS: Ubuntu 22.04 / WSL(Ubuntu) / AlmaLinux 8  
- 必要パッケージ:  
  ```bash
  sudo apt update
  sudo apt install build-essential libreadline-dev
C コンパイラ: gcc

libft: 42 で提出可能な自作 libft または公開リポジトリ

🚀 ビルド＆インストール
bash
コピーする
編集する
# リポジトリをクローン＆移動
git clone https://github.com/nekogami6666/minishell.git
cd minishell

# libft を用意（自プロジェクト or クローン）
# 例: 外部公開リポジトリを libft フォルダにクローン
git clone https://github.com/ramos21rodrigo/42porto.libft.git libft

# ビルド
make
make は自動で libft と minishell の両方をコンパイルします。

生成された minishell バイナリをプロジェクト直下に配置。

🎯 使い方
bash
コピーする
編集する
# シェルを起動
./minishell

# プロンプトが表示されたらコマンド入力
minishell$ echo Hello, World!
Hello, World!

# リダイレクト
minishell$ echo foo > out.txt
minishell$ cat < out.txt
foo

# パイプ
minishell$ seq 1 5 | rev

# 環境変数展開
minishell$ export MYVAR=42
minishell$ echo $MYVAR
42

# シグナル
# Ctrl+C → プロンプト復帰
# Ctrl+D → exit

# シェルを終了
minishell$ exit
exit
⚙️ ソース構成
less
コピーする
編集する
minishell/
├─ include/
│   ├─ minishell.h       // グローバル定義
│   ├─ lexer.h           // 字句解析
│   ├─ parser.h          // 構文解析
│   └─ builtins.h        // ビルトイン宣言
├─ src/
│   ├─ main.c            // エントリポイント
│   ├─ lexer/            // 字句解析モジュール
│   ├─ parser/           // 構文解析モジュール
│   ├─ exec/             // 実行モジュール（fork・pipe）
│   ├─ builtins/         // 各ビルトイン実装
│   └─ utils/            // 環境操作・シグナル・エラー
├─ libft/                // 42 標準 C ライブラリ
└─ Makefile
📋 制限事項 & TODO
❌ ヒアドキュメント（<<）未対応

❌ ワイルドカード展開（*）未対応

❌ 論理演算子（&&, ||）未対応

今後の拡張アイデア

ヒアドキュメント実装

ワイルドカード・グロビング

条件演算子の AST 拡張

終端文字列の入出力テスト自動化スクリプト

⚖️ ライセンス
このプロジェクトは MIT License の下で公開しています。

🤝 Contributing
Issue を立てる

フォーク＆ブランチを切る (feature/xxx)

コードを修正＆コミット

Pull Request を作成

皆さまのご意見・改善提案をお待ちしています！

markdown
コピーする
編集する

> 上記をそのまま GitHub の編集画面に貼り付け、下部の **Commit changes** ボタンを押せば `README.md` が追加されます。








ChatGPT に質問する
