#include <stumpd/authentication/authentication.hpp>
#include <stumpd/authentication/authentication_session.hpp>
#include <stumpd/authentication/htpasswd_auth_source.hpp>

stumpd::authentication_session *
stumpd::htpasswd_auth_source(authentication* auth, const char* username, const char* password)
{
  fprintf(stdout, "Yhea boi! Hit htpasswd_auth_source...\n");
  FILE *fp;
  char *line;
  std::string userpass;
  std::vector<std::string> split_userpass;

  line = (char*)malloc(sizeof(char)*1025);

  memset(line, 0, 1025);

  fp = fopen(STUMPD_AUTHENTICATION_HTPASSWD_FILE, "r");
  if(fp)
  {
    while((fgets(line, 1024, fp)) != NULL)
    {

      split_userpass =
        stumpd::utilities::split( 
          stumpd::utilities::base64::decode(line).c_str(),
          ':');

      if(strncmp(username, split_userpass[0].c_str(), strlen(username)) == 0)
      {
        if(strncmp(password, split_userpass[1].c_str(), strlen(password)) == 0)
        {
          stumpd::authentication_session *session;
          session = new stumpd::authentication_session(username, password);

          //auth->sessions.access()->push_back(session);
          auth->sessions.access()->insert(std::pair<const char *, stumpd::authentication_session*>(session->get_session_id().c_str(), session));

          fclose(fp);
          //free(session_id);
          free(line);

          return session;
        } else {
          fclose(fp);
          free(line);

          fprintf(stdout, "Passwords do not match %s : %s\n", password, split_userpass[1].c_str());

          return NULL;
        }
      } else {
        fprintf(stdout, "Username does not match: %s : %s\n", username, split_userpass[0].c_str());
      }
      memset(line, 0, 1025);
    }
    if(fp)
      fclose(fp);
    free(line);
    return NULL;
  } else {
    fprintf(stderr, "Error opening htpasswd file: %s\n", STUMPD_AUTHENTICATION_HTPASSWD_FILE);
    return NULL;
  }

}
