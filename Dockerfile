FROM patricol/sfml

WORKDIR /executable

ADD . /executable

CMD ["bash", "clientExe"]