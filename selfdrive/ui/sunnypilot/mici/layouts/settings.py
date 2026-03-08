"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
from openpilot.selfdrive.ui.mici.layouts.settings import settings as OP
from openpilot.selfdrive.ui.mici.widgets.button import BigButton, BigCircleButton
from openpilot.selfdrive.ui.mici.widgets.dialog import BigConfirmationDialogV2
from openpilot.selfdrive.ui.sunnypilot.mici.layouts.sunnylink import SunnylinkLayoutMici
from openpilot.selfdrive.ui.sunnypilot.mici.layouts.models import ModelsLayoutMici
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.lib.multilang import tr

ICON_SIZE = 70


class SettingsLayoutSP(OP.SettingsLayout):
  def __init__(self):
    OP.SettingsLayout.__init__(self)

    sunnylink_panel = SunnylinkLayoutMici(back_callback=gui_app.pop_widget)
    sunnylink_btn = BigButton("sunnylink", "", "icons_mici/settings/developer/ssh.png")
    sunnylink_btn.set_click_callback(lambda: gui_app.push_widget(sunnylink_panel))

    models_panel = ModelsLayoutMici(back_callback=gui_app.pop_widget)
    models_btn = BigButton("models", "", "../../sunnypilot/selfdrive/assets/offroad/icon_models.png")
    models_btn.set_click_callback(lambda: gui_app.push_widget(models_panel))

    self.disable_always_offroad_btn = BigCircleButton("../../sunnypilot/selfdrive/assets/icons_mici/disable_offroad.png",
                                                      red=False, icon_size=(120, 120))
    self.disable_always_offroad_btn.set_click_callback(self._disable_always_offroad)

    items = self._scroller._items.copy()

    items.insert(0, self.disable_always_offroad_btn)
    items.insert(1, sunnylink_btn)
    items.insert(2, models_btn)
    self._scroller._items.clear()
    for item in items:
      self._scroller.add_widget(item)

  def _update_state(self):
    super()._update_state()

    # Show "disable always offroad" button only when in always offroad mode
    self.disable_always_offroad_btn.set_visible(ui_state.always_offroad)

  def _disable_always_offroad(self):
    def _do_disable():
      ui_state.params.put_bool("OffroadMode", False)
      self.disable_always_offroad_btn.set_visible(False)

    dlg = BigConfirmationDialogV2(tr("slide to exit always offroad"), "icons_mici/settings/device/lkas.png",
                                  red=True, confirm_callback=_do_disable)
    gui_app.push_widget(dlg)
