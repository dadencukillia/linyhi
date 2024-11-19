# Linyhi
A beautiful and fast replacement for [neofetch](https://github.com/dylanaraps/neofetch) running in the [Kitty](https://github.com/kovidgoyal/kitty) terminal.

![screenshot 1](https://raw.github.com/dadencukillia/linyhi/main/readme_resources/screenshot1.png)
*Arts by [@iwa_to_mushi](https://twitter.com/iwa_to_mushi)*

![screenshot 2](https://raw.github.com/dadencukillia/linyhi/main/readme_resources/screenshot1.png)

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
| no | no |
</details>

<details>
<summary>Informative text (textfile)</summary>
<br>

The format of informative text must be in the file specified in the configuration file as the value of the `textfile` field.

The text will be displayed next to the image exactly as it is in the file. However, there is a way to change the color of the text, display system variables and other placeholders. To do this, you need to surround the system value with `%` characters. For example: `Hello %USER%` or `My terminal is %TERM%`.

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
| reset | reset |

**Placeholders for informative text:**
| OS | CPU | GPU | Battery | RAM | NETWORK | TERMINAL |
|----|-----|-----|---------|-----|---------|----------|
| %distro% | %cpu_name% | %gpu_name% | %battery_state% | %free_ram% | %ip% | %term% |
| %linux_version% | %cpu_logical_cores% | | %battery_charge% | %total_ram% | | %shell% |
| %uptime% | %cpu_physical_cores% | | | %avialable_ram% | | %shell_version% |
| | | | | %busy_ram% | | |
| | | | | %free_ram_gb% | | |
| | | | | %total_ram_gb% | | |
| | | | | %avialable_ram_gb% | | |
| | | | | %busy_ram_gb% | | |

</details>

## 📝 To-Do
- Add support for other terminals (Konsole, wayst, WezTerm).
- Add support for other image formats (jpeg, webp).
- Add more settings for the configuration.
- Add more placeholders to display information about the system.

## 🤝 Contribution
Contributions are welcomed. You can test the program and report bugs, update the code. It would be great if you could help format the code and help implement items from the To-Do list.

### Project structure:
- **src/terms** — a folder for protocols of different terminals.
- **src/thirdparty** — a folder containing libraries or code from the Internet that has own CMakeLists.txt file.
- **src/utils** — a folder with code that can be reused in other projects.
- **readme_resources** — a folder with resources for the README.md file.

### Building:
- `make` — build and run executable.
- `make release` — build executable for usage.
- `make exe` — run builded executable.
