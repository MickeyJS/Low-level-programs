		opt f-g-h+l+o+  ;opcje emulatora
                org $1000       ;rozpoczecie pod adresem 1000
 
start          
                lda #%10000000  ;wczytanie liczby binarnej do akumulatora
                sta byte        ;zaladowanie akumulatora do pamieci
                jsr conv        ;skok do etykiety conv
                lda word+1      ;zaladowanie do akumulatora wartosci z pod adresu word
                add #$30        ;dodanie 30 dla uzyskania kodu asci
                sta $90         ;zapisanie akumulatora pod adres 90
                lda <$90        ;zaladowanie komorki ktorej adresem jest mlodszy bajt z pod adresu 90
                ldx >$90        ;zaladowanie komorki ktorej adresem jest starszy bajt z pod adresu 90
                jsr $ff80       ;skok pod adres - procedura wyswietlajaca
                lda word        ;zaladowanie do akumulatora wartosci z pod adresu word
                lsr @           ;przesuniecie bitowe w prawo
                lsr @          
                lsr @
                lsr @
                add #$30        ;dodanie 30 dla uzyskania kodu asci
                sta $90
                lda <$90
                ldx >$90
                jsr $ff80
                lda word
                and #%00001111  ;porownanie (i) bitowe akumulatora z podana wartoscia
                add #$30
                sta $90
                lda <$90
                ldx >$90
                jsr $ff80
                brk             ;koniec programu
word            dta b(0)        ;etykieta word ktora rezerwuje miejsce dla liczby binarnej
                dta b(0)
byte            dta b(0)
conv            lda #0          ;przypisanie akumulatorowi wartosci 0
                sta word        ;zapisanie wartosci akumulatora pod adres z etykiety word
                sta word+1      ; -||- +1
                ldx #8          ;przypisanie do rejestru x wartosci 8
                sed             ;przelacza procesor w tryb 10
cv1             asl byte        ;przesuniecie w lewo bitów w liczbie spod adresu z etykiety byte
                lda word        ;zaladowanie do akumulatora wartosci spod adresy z etykiety word
                adc word        ;dodanie do akumulatora carry + wartosci spod adresu word
                sta word        ;zapisanie akumulatora pod adres z et. word
                rol word+1      ;przesuniecie bitow w lewo pod adresem word+1,carry jako 0bit i zaladowanie do carry wyrzuconego bitu (7)
                dex             ;zmniejszenie x o 1
                bne cv1         ;skok do cv1
                cld             ;wyjscie z systemu 10
                rts             ;wyjscie z podprogramu
                org $2E0
                                dta a(start)
 
                end of file     ;koniec pliku
