# Kurkur

## Overview
[🇹🇷 Türkçe](#türkçe) | [🇺🇸 English](#english)

---

## <a name="türkçe"></a>Türkçe

Kurkur, hobi amaçlı olarak kendim için geliştirdiğim, sadece macOS'ta çalışan hafif bir C++ uygulamasıdır. TCMB'nin resmi API'sinden saatlik USD/TRY ve EUR/TRY alış-satış kurlarını çekip terminal üzerinde bildirim olarak gösterir.

### Özellikler

- ⏱️ Saatlik güncel döviz kuru bildirimleri
- 💱 USD/TRY ve EUR/TRY için hem alış hem satış kurları
- 🖥️ Basit, rahatsız etmeyen komut satırı arayüzü
- 🪶 Minimal kaynak kullanımı
- 🍎 Sadece macOS sistemlerde çalışır

### Veri Kaynağı

Tüm döviz kuru verileri Türkiye Cumhuriyet Merkez Bankası'nın (TCMB) resmi API'sinden alınmaktadır:
- API URL: https://www.tcmb.gov.tr/kurlar/today.xml

### Kullanım

```bash
# Uygulamayı başlatmak için
./kurkur

# Çıkmak için
# Sadece 'e' tuşuna basıp Enter'a basın
```

---

## <a name="english"></a>English

Kurkur is a lightweight C++ application that I developed for myself as a hobby project. It only works on macOS and retrieves hourly USD/TRY and EUR/TRY exchange rates from the Central Bank of the Republic of Turkey's official API, displaying them as notifications in your terminal.

### Features

- ⏱️ Hourly notifications with up-to-date exchange rates
- 💱 Both buying and selling rates for USD/TRY and EUR/TRY
- 🖥️ Simple, unobtrusive command-line interface
- 🪶 Minimal resource usage
- 🍎 Works exclusively on macOS

### Data Source

All exchange rate data comes from the Central Bank of the Republic of Turkey (TCMB) via their official API:
- API URL: https://www.tcmb.gov.tr/kurlar/today.xml

### Usage

```bash
# Start the application
./kurkur

# Exit
# Simply press 'e' and then Enter
``` 