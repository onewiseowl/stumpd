$.extend(widgets, {
  navMenu : ({
    draw : function() {
      $('body').append(
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
                  href: '/search'
                }).html('search')
              ),
              $('<td></td>').append(
                $('<a></a>').attr({
                  id: '_navMenu_tools',
                  name: '_navMenu_tools',
                  class: '_navMenu_tools',
                  href: '/tools'
                }).html('tools')
              ),
              $('<td></td>').append(
                $('<a></a>').attr({
                  id: '_navMenu_admin',
                  name: '_navMenu_admin',
                  class: '_navMenu_admin',
                  href: '/admin'
                }).html('admin')
              ),
              $('<td></td>').append(
                $('<a></a>').attr({
                  id: '_navMenu_logout',
                  name: '_navMenu_logout',
                  class: '_navMenu_logout',
                  href: '/logout'
                }).html('logout')
              )
            )
          ).fadeIn(1500)
      )
    }
  })
});
