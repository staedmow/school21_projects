FROM nginx
WORKDIR /home/
COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./my_server.c /home/my_server.c
COPY ./run.sh /home/run.sh
RUN apt-get update && apt-get install -y gcc spawn-fcgi libfcgi-dev; \
    #DKL-DI-0005
    rm -rf /var/lib/apt/lists/*; \
    chown -R nginx:nginx /etc/nginx/nginx.conf; \
    chown -R nginx:nginx /var/cache/nginx; \
    chown -R nginx:nginx /home; \
    touch /var/run/nginx.pid; \
    chown -R nginx:nginx /var/run/nginx.pid; \
    #CIS-DI-0008
    chmod u-s /usr/bin/gpasswd; \
    chmod g-s /usr/bin/chage; \
    chmod g-s /usr/sbin/unix_chkpwd; \
    chmod u-s /usr/bin/mount; \
    chmod g-s /usr/bin/expiry; \
    chmod u-s /usr/bin/chsh; \
    chmod u-s /usr/bin/su; \
    chmod u-s /usr/bin/umount; \
    chmod u-s /usr/bin/chfn; \
    chmod u-s /usr/bin/newgrp; \
    chmod u-s /usr/bin/passwd;
USER nginx
ENTRYPOINT ["sh", "./run.sh"]
#CIS-DI-0006
HEALTHCHECK CMD curl -f http://localhost/ || exit 1