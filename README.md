# <svg role="img" width="20" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><title>GNOME Terminal</title><path fill="white" d="M1.846 0A1.841 1.841 0 000 1.846v18.463c0 1.022.823 1.845 1.846 1.845h20.308A1.841 1.841 0 0024 20.31V1.846A1.841 1.841 0 0022.154 0H1.846zm0 .924h20.308c.512 0 .922.41.922.922v18.463c0 .511-.41.921-.922.921H1.846a.919.919 0 01-.922-.921V1.846c0-.512.41-.922.922-.922zm0 .922v18.463h20.308V1.846H1.846zm1.845 2.14l3.235 1.758v.836L3.69 8.477V7.385l2.243-1.207v-.033L3.69 5.076v-1.09zM7.846 9.23h3.693v.924H7.846V9.23zM0 21.736v.418C0 23.177.823 24 1.846 24h20.308A1.841 1.841 0 0024 22.154v-.418a2.334 2.334 0 01-1.846.918H1.846A2.334 2.334 0 010 21.736Z"/></svg> Linyhi
A beautiful and fast replacement for [neofetch](https://github.com/dylanaraps/neofetch) running in the [Kitty](https://github.com/kovidgoyal/kitty) terminal.

![screenshot](https://raw.github.com/dadencukillia/linyhi/main/readme_resources/screenshot.png)
*Arts by [@iwa_to_mushi](https://twitter.com/iwa_to_mushi)*

## 📥️ Installation
**! The project is available only on Linux-based operating systems and in the Kitty terminal.**
1. For now, you can only build an executable file yourself or download one [here](https://github.com/dadencukillia/linyhi/releases).
2. Put the executable file in the /usr/bin folder and grant the command execution rights:
```
chmod +x /usr/bin/linyhi
```
3. Create a configuration folder at `~/.config/linyhi` and the `config.lh` file in it.
4. Customize the configuration file (the next paragraph can help you with this).
5. Run the command `linyhi` in your Kitty terminal.
6. Also, you can add the line `linyhi` to the end of the file `~/.bashrc`.

## ⚙️ Configuration
You can see the example of the ~/.config/linyhi folder at [link](https://github.com/dadencukillia/linyhi/tree/main/readme_resources/linyhi).

<details>
<summary>Configuration file (config.lh)</summary>
<br>

There must be a file `config.lh` in the configuration folder.

`.lh` - a special format of the configuration file. Features:
- You can make comments at the beginning of a line using the “#” character.
- Any other line must be in the “key: value” format.
- The key must: not contain spaces, end with the character “:”.
- Values can be of the following types: character (char), string, boolean, long, non-negative number (unsigned long).
- A string value can be set with or without the “ character.

Well, here's what you can customize in linyhi:
| Key | Type | Description |
|-----|------|-------------|
| textfile | String | The path to the text file whose text will be displayed to the right of the picture. You can learn how to set up this file in the next section. |
| imagesdirectory | String | A folder with images that will be randomly selected and displayed to the left of the informative text. **Important:** all images should be in PNG format, and they are not automatically scaled, so save them in the size that should be displayed in the terminal window. |
| paddingx | non-negative number | Left indents from the edges of the terminal window (number of space characters). |
| paddingy | non-negative number | Top and bottom indents from the edges of the terminal window, past and next command lines (number of line break characters). |
| gap | non-negative number | Indent the informative text from the picture in the spaces. |
| clearconsole | boolean (yes/no/true/false) | If yes or true, the program will clear the console after each program launch. |
| croptextheight | boolean (yes/no/true/false) | If so, the lines of informative text that do not fit within the height of the image will not be displayed. |
| border | character | The character that will form the column that separates the informative text from the image. If you want no column, leave a space here. |
| bordercolor | String | The color of the column between the image and the informative text. You can see the list of possible values below. |

**Color values for bordercolor field:**
| Regular | Bright |
|---------|--------|
| black | gray / grey / bright black |
| red | bright red |
| green | bright green |
| yellow | bright yellow |
| blue | bright blue |
| magenta | bright magenta |
| cyan | bright cyan |
| white | bright white |
| no |
</details>

<details>
<summary>Informative text (textfile)</summary>
<br>

The format of informative text must be in the file specified in the configuration file as the value of the `textfile` field.

The text will be displayed next to the image exactly as it is in the file. However, there is a way to change the color of the text, display system variables and other placeholders (not yet implemented). To do this, you need to surround the system value with `%` characters. For example: `Hello %USER%` or `My terminal is %TERM%`.

To color, surround the name of the color in lowercase letters with `%` symbols. For example: `%red%This text should be red.` or `%red%Red%reset% and %gray%gray%reset% and default.`. Also note that the color is reset every line.

**Color values for informative text:**
| Regular | Bright |
|---------|--------|
| black | gray |
| red | bright_red |
| green | bright_green |
| yellow | bright_yellow |
| blue | bright_blue |
| magenta | bright_magenta |
| cyan | bright_cyan |
| white | bright_white |
| reset |
</details>

## 📝 To-Do
- Add support for other terminals (Konsole, wayst, WezTerm)
- Add support for other image formats (jpeg, webp).
- Add more settings for the configuration.
- Add placeholders to display information about the system.

## 🤝 Contribution
Contributions are welcomed. You can test the program and report bugs, update the code. It would be great if you could help format the code and help implement items from the To-Do list.

### Project structure:
- **src/terms** — a folder for protocols of different terminals
- **src/thirdparty** — a folder containing libraries or code from the Internet.
- **src/utils** — a folder with code that can be reused in other projects.
- **readme_resources** — a folder with resources for the README.md file.

### Building:
- `make` — build and run executable.
- `make release` — build executable for usage.
- `make exe` — run builded executable.