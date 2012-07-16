$.extend(widgets, {
  index : ({
    logoBox : ({
      draw : function () {
        $('body').append(
          $('<div></div>').attr({
            id : '_logoBox',
            name : '_logoBox',
            class : '_logoBox'
          }).html('s t u m p')
        );
      }
    }),
    loginBox : ({
      submit : function () {
        $.ajax({
          url : '/api',
          type : 'POST',
          data : {
            action : 'login',
            username : $('#_loginBox_username_input')[0].value,
            password : $('#_loginBox_password_input')[0].value
          },
          statusCode : {
            200 : function () {
              $(location).attr({href : '/home'});
            },
            401 : function () {
              alert('Aw shit, login failed :(');
            },
            404 : function () {
              alert('Um, 404?');
            }
          }
        })
      },
      draw : function () {
        $('body').append(
          $('<div></div>').attr({
            id : '_loginBox',
            name : '_loginBox',
            class : '_loginBox'
          }).append(
            $('<form></form>').attr({
               id : '_loginBox_form',
               name : '_loginBox_form',
               class : '_loginBox_form',
               method : 'POST',
               action : '/api'
            }).append(
              $('<table></table>').append(
                $('<tr></tr>').append(
                  $('<td></td>').html('username: '),
                  $('<td></td>').append(
                    $('<input></input>').attr({
                      type : 'text',
                      id : '_loginBox_username_input',
                      name : 'username',
                      class : '_loginBox_username_input'
                    })
                  )
                ),
                $('<tr></tr>').append(
                  $('<td></td>').html(
                    'password: '
                  ),
                  $('<td></td>').append(
                    $('<input></input>').attr({
                      type : 'password',
                      id : '_loginBox_password_input',
                      name : 'password',
                      class : '_loginBox_password_input'
                    })
                  )
                )
              ),
              $('<input></input>').attr({
                type : 'hidden',
                id : '_loginBox_api_action',
                name : 'action',
                value : 'login'
              }),
              $('<a></a>').attr({
                href : '#',
                onClick : 'Javascript: widgets.index.loginBox.submit();',
                id   : '_loginBox_submit',
                name : '_loginBox_submit',
                class : '_loginBox_submit'
              }).html('Submit'),
              $('<br />')
            )
          ).fadeIn(1200)
        )
      }
    })
  })
});
