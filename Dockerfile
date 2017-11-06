FROM patricol/sfml

WORKDIR /executable

ADD . /executable

RUN eopkg it SFML

RUN eopkg it SFML-devel

CMD ["bash", "clientExe"]