
$.extend(widgets, {
  tools : ({
    filters : ({
      list : [{}],
      getExisting : function() {
        $.ajax({
        url : "/api",
        type : "POST",
        async : true,
        data : {
          action : 'getFilters'
        },
        success : function(data, textStatus, jqXHR) {
          try {
            widgets.tools.filters.list = eval(data);
          } catch(e) {
            alert(e);
          }
        }
      });
      },
      menu : ({
        draw : function() {
          widgets.tools.filters.getExisting();
          if($('div#_toolsFiltersMenu').length > 0)
          {
            $('div#_toolsFiltersMenu').empty().remove();
          }

          $('body').append(
            $('<div></div>').attr({
              id : '_toolsFiltersMenu',
              name : '_toolsFiltersMenu',
              class : '_toolsFiltersMenu'
            }).append(
              $('<table></table>').append(
                $('<tr></tr>').append(
                  $('<td></td>').text('Alias'),
                  $('<td></td>').append(
                    $('<input></input>').attr({
                      id : '_toolsFilterAlias',
                      name : '_toolsFilterAlias',
                      class : '_toolsFilterAlias'
                    })
                  )
                )
              )
            )
          );
        }
      }),
      draw : function() {
        widgets.tools.filters.menu.draw();
      }
    }),
    menu : ({
      draw : function() {
        widgets.navMenu.draw();
        $('body').append(
          $('<div></div>').attr({
            id : '_toolsMenu',
            name : '_toolsMenu',
            class : '_toolsMenu'
          }).append(
            $('<table></table>').attr({
              id : '_toolsMenu_table',
              name : '_toolsMenu_table',
              class : '_toolsMenu_table'
            }).append(
              $('<tr></tr>').append(
                $('<td></td>').append(
                  $('<a></a>').attr({
                    href : 'Javascript: widgets.tools.filters.menu.draw()'
                  }).text('filters')
                ),
                $('<td></td>').append(
                  $('<a></a>').attr({
                    href : 'Javascript: widgets.tools.actions.menu.draw()'
                  }).text('actions')
                ),
                $('<td></td>').append(
                  $('<a></a>').attr({
                    href : 'Javascript: widgets.tools.interpreter.menu.draw()'
                  }).text('JS interpreter')
                )
              )
            )
          )
        );
      }
    }),
    draw : function() {
      widgets.tools.menu.draw();
      widgets.tools.filters.draw();
    }
  })
});
