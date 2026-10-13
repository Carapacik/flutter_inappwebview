#include <gtest/gtest.h>

#include "in_app_webview/in_app_webview_settings.h"

#ifdef HAVE_WPE_PLATFORM
#include <wpe/headless/wpe-headless.h>
#include <wpe/wpe-platform.h>

namespace flutter_inappwebview_plugin {

// No display connection or WebProcess is needed to exercise WPESettings.
TEST(WpePlatformSettings, AppliesAndClearsReducedMotionPreference) {
  g_autoptr(WPEDisplay) display = wpe_display_headless_new();
  ASSERT_NE(display, nullptr);
  WPESettings* preferences = wpe_display_get_settings(display);
  ASSERT_NE(preferences, nullptr);
#ifdef WPE_SETTING_REDUCED_MOTION
  const char* key = WPE_SETTING_REDUCED_MOTION;
#else
  const char* key = WPE_SETTING_DISABLE_ANIMATIONS;
#endif

  InAppWebViewSettings settings;
  for (bool value : {true, false}) {
    settings.disableAnimations = value;
    settings.applyWpePlatformSettings(display);
    GError* error = nullptr;
    const bool actual = wpe_settings_get_boolean(preferences, key, &error);
    EXPECT_EQ(error, nullptr);
    EXPECT_EQ(actual, value);
    g_clear_error(&error);
  }
}

}  // namespace flutter_inappwebview_plugin
#endif
