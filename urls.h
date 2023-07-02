#ifndef URLS_H
#define URLS_H

#include <QUrl>

namespace JD {

static const char loginUrl[]    = "https://passport.jd.com/new/login.aspx";
static const char homeUrl[]     = "https://www.jd.com/";
static const char qrCodeSrc[]   = "https://qr.m.jd.com/show?appid=133&size=147&t=%1&sa=1";
static const char addItemUrl[]  = "https://cart.jd.com/gate.action?pid=%1&pcount=%2&ptype=1";
static const char checkoutUrl[] = "https://trade.jd.com/shopping/order/getOrderInfo.action";
static const auto urlCompareRules = QUrl::RemoveFilename | QUrl::NormalizePathSegments | QUrl::RemoveQuery;
static const char orderScriptHeader[] = R"(
// ==UserScript==
// @name my_submit_order
// @include https://trade.jd.com/shopping/order/getOrderInfo.action
// @run-at document-end
// ==/UserScript==
)";

} // namespace JD

#endif // URLS_H
