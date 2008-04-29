#!/bin/bash

base_path=$(dirname $0)

LD_LIBRARY_PATH=${base_path}/EVE_API_Qt/bin:${base_path}/EVE_Manager/bin ${base_path}/EVE_API_Qt/bin/EVE_API_Qt_base_app