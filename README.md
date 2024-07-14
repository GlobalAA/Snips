### Tray snippets

#### Простая програмка, которая позволит вам открывать сайты или исполнять команды прямо из трея вашей ос

#### Параметры конфига (конфиг должен иметь название cfg.json, и наъодиться в одной папке с приложением)

- sites
    * url - ссылка на сайт
    * title - название в меню приложения

- commands
    * command - команда
    * title - название в меню приложения
    
```json
{
    "sites": [
        {
            "title": "Google",
            "url": "https://google.com"
        },
        {
            "title": "ChatGpt",
            "url": "https://chatgpt.com/"
        },
        {
            "title": "stackoverflow",
            "url": "https://stackoverflow.com/"
        }
    ],
    "commands": [
        {
            "title": "Open docs",
            "command": "open ~/Documents"
        }
    ]
}

```
