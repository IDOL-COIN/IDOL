#ifndef GUICONSTANTS_H
#define GUICONSTANTS_H

/* Milliseconds between model updates */
static const int MODEL_UPDATE_DELAY = 500;

/* AskPassphraseDialog -- Maximum passphrase length */
static const int MAX_PASSPHRASE_SIZE = 1024;

/* BitcoinGUI -- Size of icons in status bar */
static const int STATUSBAR_ICONSIZE = 16;

/* Invalid field background style */
#define STYLE_INVALID "background:#FF8080"

/* Transaction list -- unconfirmed transaction */
#define COLOR_UNCONFIRMED QColor(164, 164, 164)
/* Transaction list -- negative amount */
#define COLOR_NEGATIVE QColor(252, 52, 52)
/* Transaction list -- bare address (without label) */
#define COLOR_BAREADDRESS QColor(192, 192, 192)

/* Tooltips longer than this (in characters) are converted into rich text,
   so that they can be word-wrapped.
 */
static const int TOOLTIP_WRAP_THRESHOLD = 80;

/* Maximum allowed URI length */
static const int MAX_URI_LENGTH = 255;

/* QRCodeDialog -- size of exported QR Code image */
#define EXPORT_IMAGE_SIZE 256

/* Colors for minting tab for each coin age group */
#define COLOR_MINT_YOUNG QColor(90, 132, 218)
#define COLOR_MINT_MATURE QColor(11, 211, 177)
#define COLOR_MINT_OLD QColor(255, 98, 190)

#endif // GUICONSTANTS_H
