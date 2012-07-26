
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
          if($('div#_toolsSubMenu').length > 0)
          {
            $('div#_toolsSubMenu').empty().remove();
          }

          $('body').append(
            $('<div></div>').attr({
              id : '_toolsSubMenu',
              name : '_toolsSubMenu',
              class : '_toolsSubMenu'
            }).append(
              $('<table></table>').append(
                $('<tr></tr>').append(
                  $('<td></td>').text('Alias'),
                  $('<td></td>').append(
                    $('<a></a>').attr({
                      id : '_toolsFilter_new',
                      name : '_toolsFilter_new',
                      class : '_toolsFilter_new',
                      href : 'Javascript: widgets.tools.filters.new.draw();'
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
    interpreter : ({
      submit : function() {
        $.ajax({
        url : "/api",
        type : "POST",
        async : true,
        contentType: 'application/x-www-form-urlencoded',
        data : {
          action : 'testScript',
          script : editAreaLoader.getValue('_jsInterpreter_textarea')
        },
        success : function(data, textStatus, jqXHR) {
          alert('Code successfully interpreted');
        },
        error : function(jqXHR, textStatus, errorThrown) {
          alert('Code interpretation error: ' + errorThrown + " " + textStatus);
        }
      });
      },
      draw : function() {
        if($('div#_toolsSubMenu').length > 0)
        {
          $('div#_toolsSubMenu').empty().remove();
        }
        //include('/edit_area/edit_area_loader.js');
        //include('/edit_area/edit_area_full.js');
        $('body').append(
          $('<div></div>').attr({
            id : '_toolsSubMenu',
            name : '_toolsSubMenu',
            class : '_toolsSubMenu'
          }).append(
            $('<textarea></textarea>').attr({
              id : '_jsInterpreter_textarea',
              name : 'content',
              class : '_jsInterpreter_textarea'
            }),
            $('<a></a>').attr({
              id: '_jsInterpreter_submit',
              name: '_jsInterpreter_submit',
              class: '_jsInterpreter_submit',
              href : 'Javascript: widgets.tools.interpreter.submit()'
            }).text('Check syntax')
          )
        );
        editAreaLoader.init({
          id: '_jsInterpreter_textarea',
          start_highlight: true,
          allow_toggle: false,
          word_wrap: true,
          language: 'en',
          syntax: 'js'
        });
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
                    href : 'Javascript: widgets.tools.interpreter.draw()'
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
