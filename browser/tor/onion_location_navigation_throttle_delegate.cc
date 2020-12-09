/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/tor/onion_location_navigation_throttle_delegate.h"

#include <utility>

#include "brave/browser/tor/tor_profile_manager.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "content/public/browser/web_contents.h"

namespace tor {

namespace {

void OnTorProfileCreated(GURL onion_location,
                         Profile* profile,
                         Profile::CreateStatus status) {
  if (status != Profile::CreateStatus::CREATE_STATUS_INITIALIZED)
    return;
  Browser* browser = chrome::FindTabbedBrowser(profile, true);
  if (!browser)
    return;
  content::OpenURLParams open_tor(onion_location, content::Referrer(),
                                  WindowOpenDisposition::NEW_FOREGROUND_TAB,
                                  ui::PAGE_TRANSITION_TYPED, false);
  browser->OpenURL(open_tor);
}

}  // namespace

OnionLocationNavigationThrottleDelegate::
    OnionLocationNavigationThrottleDelegate() = default;

OnionLocationNavigationThrottleDelegate::
    ~OnionLocationNavigationThrottleDelegate() = default;

void OnionLocationNavigationThrottleDelegate::OpenInTorWindow(
    content::WebContents* web_contents,
    GURL onion_location) {
  Profile* profile =
      Profile::FromBrowserContext(web_contents->GetBrowserContext());
  TorProfileManager::SwitchToTorProfile(profile,
      base::BindRepeating(&OnTorProfileCreated, std::move(onion_location)));

  // We do not close last tab of the window
  Browser* browser = chrome::FindBrowserWithProfile(profile);
  if (browser && browser->tab_strip_model()->count() > 1)
    web_contents->ClosePage();
}

}  // namespace tor