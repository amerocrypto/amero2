// Public Resource β 2021 Satoshi Nakamoto
// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_WARNINGS_H
#define BITCOIN_WARNINGS_H

#include <stdlib.h>
#include <string>

void SetMiscWarning(const std::string& strWarning);
void SetfLargeWorkForkFound(bool flag);
bool GetfLargeWorkForkFound();
void SetfLargeWorkInvalidChainFound(bool flag);
/** Format a string that describes several potential problems detected by the core.
 * @param[in] strFor can have the following values:
 * - "statusbar": get the most important warning
 * - "gui": get all warnings, translated (where possible) for GUI, separated by <hr />
 * @returns the warning string selected by strFor
 */
std::string GetWarnings(const std::string& strFor);

#endif //  BITCOIN_WARNINGS_H
