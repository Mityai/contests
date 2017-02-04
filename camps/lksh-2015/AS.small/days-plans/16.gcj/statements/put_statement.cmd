scp -i C:\WorkGit\Keys\id_rsa %* ejudge@ejudge.lksh.ru:/var/www/vhosts/sis/AS/statements
ssh -i C:\WorkGit\Keys\id_rsa ejudge@ejudge.lksh.ru chmod 0664 /var/www/vhosts/sis/AS/statements/{%*}
