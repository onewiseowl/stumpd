
$.extend(widgets, {
  tools : ({
    filters : ({
      list : Array(),
      update : function(id) {
        if(typeof widgets.tools.interpreter.submit($.base64.encode(editAreaLoader.getValue('_filterList_table_edit_textarea'))) != 'undefined')
        {
          $.ajax({
            url : "/api",
            type : "POST",
            async : false,
            timeout: 2000,
            data : {
              action : 'updateFilter',
              alias : $.base64.encode(widgets.tools.filters.list[id][1]),
              filter : $.base64.encode(editAreaLoader.getValue('_filterList_table_edit_textarea')),
              id : widgets.tools.filters.list[id][0]
            },
            complete : function(jqXHR, textStatus)
            {
              if(textStatus == "timeout")
              {
                alert("Timeout!");
              }
            },
            success : function(data, textStatus, jqXHR) {
              try {
                widgets.tools.filters.getExisting();
              } catch(e) {
                alert(e);
              }
            }
          });
        }        
      },
      add : ({
        submit : function() {
          if(typeof widgets.tools.interpreter.submit($.base64.encode(editAreaLoader.getValue('_filterList_table_edit_textarea'))) != 'undefined')
          {
            $.ajax({
              url : "/api",
              type : "POST",
              async : false,
              timeout: 2000,
              data : {
                action : 'addFilter',
                alias : $.base64.encode($('input#_addFilter_alias_input').val()),
                filter : $.base64.encode(editAreaLoader.getValue('_filterList_table_edit_textarea')),
              },
              complete : function(jqXHR, textStatus)
              {
                if(textStatus == "timeout")
                {
                  alert("Timeout!");
                }
              },
              success : function(data, textStatus, jqXHR) {
                try {
                  widgets.tools.filters.getExisting();
                } catch(e) {
                  alert(e);
                }
              }
            });
          } else {
            alert("Script evaled badly...did not return 0");
          }
        },
        draw : function() {
          try {
            if($('div#_filterList_table_edit_div').length > 0)
            {
              $('div#_filterList_table_edit_div').empty().remove();
            }
            $('body').append(
              $('<div></div>').attr({
                id: '_filterList_table_edit_div',
                name: '_filterList_table_edit_div',
                class: '_filterList_table_edit_div'
              }).append(
                $('<input></input>').attr({
                  type : 'text',
                  id : '_addFilter_alias_input',
                  name : '_addFilter_alias_input',
                  class : '_addFilter_alias_input'
                }),
                $('<textarea></textarea>').attr({
                  id: '_filterList_table_edit_textarea',
                  name: '_filterList_table_edit_textarea',
                  class: '_filterList_table_edit_textarea'
                }).val('function(var data) {\n\n}\n')
              )
            );
            //editAreaLoader.hide('_filterList_table_edit_textarea');
            var m = $('div#_filterList_table_edit_div').
              dialog({
                modal: true,
                minWidth: 540,
                width: 1000,
                close: function() {
                  try {
                    editAreaLoader.delete_instance('_filterList_table_edit_textarea');
                  } catch(e) {
                    alert(e);
                  }
                }
              });
            editAreaLoader.init({
              id: '_filterList_table_edit_textarea',
              start_highlight: true,
              allow_toggle: false,
              word_wrap: true,
              language: 'en',
              min_width: 965,
              min_height: 300,
              toolbar: 'undo, redo, search, save',
              save_callback: 'widgets.tools.filters.add.submit()',
              syntax: 'js'
            });
            //editAreaLoader.show('_filterList_table_edit_textarea');
          } catch(e) {
            alert(e);
          }
        }
      }),
      edit : function(id) {
        try {
          if($('div#_filterList_table_edit_div').length > 0)
          {
            $('div#_filterList_table_edit_div').empty().remove();
          }
          $('body').append(
            $('<div></div>').attr({
              id: '_filterList_table_edit_div',
              name: '_filterList_table_edit_div',
              class: '_filterList_table_edit_div'
            }).append(
              $('<textarea></textarea>').attr({
                id: '_filterList_table_edit_textarea',
                name: '_filterList_table_edit_textarea',
                class: '_filterList_table_edit_textarea'
              })
            )
          );
          //editAreaLoader.hide('_filterList_table_edit_textarea');
          $('textarea#_filterList_table_edit_textarea').val(widgets.tools.filters.list[id][2]);
          var m = $('div#_filterList_table_edit_div').
            dialog({
              modal: true,
              minWidth: 540,
              width: 1000,
              close: function() {
                try {
                  editAreaLoader.delete_instance('_filterList_table_edit_textarea');
                } catch(e) {
                  alert(e);
                }
              }
            });
          editAreaLoader.init({
            id: '_filterList_table_edit_textarea',
            start_highlight: true,
            allow_toggle: false,
            word_wrap: true,
            language: 'en',
            min_width: 965,
            min_height: 300,
            toolbar: 'undo, redo, search, save',
            save_callback: 'widgets.tools.filters.update(' + id + ')',
            syntax: 'js'
          });
          //editAreaLoader.show('_filterList_table_edit_textarea');
        } catch(e) {
          alert(e);
        }
      },
      getExisting : function() {
        $.ajax({
        url : '/api',
        type : 'POST',
        async : false,
        timeout: 2000,
        data : {
          action : 'getFilters'
        },
        complete : function(jqXHR, textStatus)
        {
          if(textStatus == 'timeout')
          {
            alert('Timeout!');
          }
        },
        success : function(data, textStatus, jqXHR) {
          try {
            temp_data = eval(data);
            for(i in temp_data)
            {
              temp_data[i][2] = $.base64.decode(temp_data[i][2]);
            }
            widgets.tools.filters.list = temp_data
            delete temp_data;
          
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
              $('<a></a>').attr({
                id : '_addFilter_link',
                name : '_addFilter_link',
                class : '_addFilter_link',
                href : 'Javascript: widgets.tools.filters.add.draw();'
              }).text('+ add new filter'),
              $('<br />'),
              $('<br />'),
              $('<table></table>').attr({
                id : '_filterList_table',
                name : '_filterList_table',
                class : '_filterList_table',
                align: 'left'
              }).append(
                $('<tr></tr>').attr({
                  class : '_filterList_table'
                }).append(
                  $('<td></td>').attr({
                    class: "_filterList_table"
                  }).text('alias'),
                  $('<td></td>').attr({
                    class: "_filterList_table"
                  }).text('action')
                )
              )
            )
          );
          for(i in widgets.tools.filters.list)
          {
            $('table#_filterList_table').append(
              $('<tr></tr>').attr({
                class: "_filterList_table"
              }).append(
                $('<td></td>').attr({
                  class: "_filterList_table"
                }).text(widgets.tools.filters.list[i][1]),
                $('<td></td>').attr({
                  class: "_filterList_table"
                }).append(
                  /*$('<textarea></textarea>').attr({
                    readonly: "readonly"
                  }).text(
                    $.base64.decode(widgets.tools.filters.list[i][2])
                  )*/
                  $('<a></a>').attr({
                    id : '_filterList_table_edit_link',
                    name: '_filterList_table_edit_link',
                    href : 'Javascript: widgets.tools.filters.edit(' + i + ')'
                  }).text('edit |'),
                  $('<a></a>').attr({
                    id : '_filterList_table_delete_link',
                    name : '_filterList_table_delete_link',
                    href : 'Javascript: widgets.tools.filters.delete(' + i + ')'
                  }).text(' delete')
                )
              )
            );
          }
          }
        }
      ),
      draw : function() {
        widgets.tools.filters.menu.draw();
      }
    }),
    triggers : ({
      list : Array(),
      add : ({
        draw : function() {
          $('body').append(
            $('<textarea></textarea>')
          );
        }
      }),
      edit : function(id) {
        try {
          if($('div#_filterList_table_edit_div').length > 0)
          {
            $('div#_filterList_table_edit_div').empty().remove();
          }
          $('body').append(
            $('<div></div>').attr({
              id: '_filterList_table_edit_div',
              name: '_filterList_table_edit_div',
              class: '_filterList_table_edit_div'
            }).append(
              $('<textarea></textarea>').attr({
                id: '_filterList_table_edit_textarea',
                name: '_filterList_table_edit_textarea',
                class: '_filterList_table_edit_textarea'
              })
            )
          );
          //editAreaLoader.hide('_filterList_table_edit_textarea');
          alert("Trigger list empty");
          $('textarea#_filterList_table_edit_textarea').val(widgets.tools.triggers.list[id][2]);
          var m = $('div#_filterList_table_edit_div').
            dialog({
              modal: true,
              minWidth: 540,
              width: 1000,
              close: function() {
                try {
                  editAreaLoader.delete_instance('_filterList_table_edit_textarea');
                } catch(e) {
                  alert(e);
                }
              }
            });
          editAreaLoader.init({
            id: '_filterList_table_edit_textarea',
            start_highlight: true,
            allow_toggle: false,
            word_wrap: true,
            language: 'en',
            min_width: 965,
            min_height: 300,
            syntax: 'js'
          });
          //editAreaLoader.show('_filterList_table_edit_textarea');
        } catch(e) {
          alert(e);
        }
      },
      getExisting : function() {
        $.ajax({
        url : "/api",
        type : "POST",
        async : false,
        timeout: 2000,
        data : {
          action : 'getTriggers'
        },
        complete : function(jqXHR, textStatus)
        {
          if(textStatus == "timeout")
          {
            alert("Timeout!");
          }
        },
        success : function(data, textStatus, jqXHR) {
          try {
            temp_data = eval(data);
            for(i in temp_data)
            {
              alert("GET for existing triggers failed");
              temp_data[i][1] = $.base64.decode(temp_data[i][1]);
            }
            widgets.tools.triggers.list = temp_data;
            delete temp_data;
          } catch(e) {
            alert(e);
          }
        }
      });
      },
      menu : ({
        draw : function() {
          widgets.tools.triggers.getExisting();
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
              $('<table></table>').attr({
                id : '_filterList_table',
                name : '_filterList_table',
                class : '_filterList_table',
                align: 'left'
              }).append(
                $('<tr></tr>').attr({
                  class : '_filterList_table'
                }).append(
                  $('<td></td>').attr({
                    class: "_filterList_table"
                  }).text('alias'),
                  $('<td></td>').attr({
                    class: "_filterList_table"
                  }).text('action')
                )
              )
            )
          );
          for(i in widgets.tools.triggers.list)
          {
            $('table#_filterList_table').append(
              $('<tr></tr>').attr({
                class: "_filterList_table"
              }).append(
                $('<td></td>').attr({
                  class: "_filterList_table"
                }).text(widgets.tools.triggers.list[i][1]),
                $('<td></td>').attr({
                  class: "_filterList_table"
                }).append(
                  /*$('<textarea></textarea>').attr({
                    readonly: "readonly"
                  }).text(
                    $.base64.decode(widgets.tools.triggers.list[i][2])
                  )*/
                  $('<a></a>').attr({
                    id : '_filterList_table_edit_link',
                    name: '_filterList_table_edit_link',
                    href : 'Javascript: widgets.tools.triggers.edit(' + i + ')'
                  }).text('edit |'),
                  $('<a></a>').attr({
                    id : '_filterList_table_delete_link',
                    name : '_filterList_table_delete_link',
                    href : 'Javascript: widgets.tools.triggers.delete(' + i + ')'
                  }).text(' delete')
                )
              )
            );
          }
          }
        }
      ),
      draw : function() {
        widgets.tools.triggers.menu.draw();
      }
    }),
    interpreter : ({
      submit : function(data) {
        return $.ajax({
        url : "/api",
        type : "POST",
        async : true,
        contentType: 'application/x-www-form-urlencoded',
        data : {
          action : 'testScript',
          script : data
        },
        success : function(data, textStatus, jqXHR) {
          alert('Code successfully interpreted');
          return 0;
        },
        error : function(jqXHR, textStatus, errorThrown) {
          alert('Code interpretation error: ' + errorThrown + " " + textStatus + " : " + jqXHR.responseText);
          return 1;
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
              href : 'Javascript: void(0)',
              onClick : 'Javascript: widgets.tools.interpreter.submit($.base64.encode(editAreaLoader.getValue(\'_jsInterpreter_textarea\')));'
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
                    href : 'Javascript: widgets.tools.triggers.menu.draw()'
                  }).text('triggers')
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
