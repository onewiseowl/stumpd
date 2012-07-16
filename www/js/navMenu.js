$.extend(widgets, {
  navMenu : ({
    draw : function() {
      $('body').append(
        $('<div></div>').attr({
          id : '_navMenu',
          name : '_navMenu',
          class : '_navMenu'
        }).append(
          $('<div></div>').attr({
            id : '_logoBox',
            name : '_logoBox',
            class : '_logoBox'
          }).html('s t u m p'),
          $('<table></table>').attr({
            id : '_navMenu_table',
            name : '_navMenu_table',
            class : '_navMenu_table'
          }).append(
            $('<tr></tr>').append(
              $('<td></td>').append(
                $('<a></a>').attr({
                  id: '_navMenu_search',
                  name: '_navMenu_search',
                  class: '_navMenu_search',
                  href: 'Javascript: alert("search")'
                }).html('search')
              ),
              $('<td></td>').append(
                $('<a></a>').attr({
                  id: '_navMenu_tools',
                  name: '_navMenu_tools',
                  class: '_navMenu_tools',
                  href: 'Javascript: alert("tools")'
                }).html('tools')
              ),
              $('<td></td>').append(
                $('<a></a>').attr({
                  id: '_navMenu_logout',
                  name: '_navMenu_logout',
                  class: '_navMenu_logout',
                  href: 'Javascript: alert("logout")'
                }).html('logout')
              )
            )
          )
        )
      )
    }
  })
});
