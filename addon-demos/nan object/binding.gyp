{
  "targets": [{
    "target_name": "addon",
    "sources": [
      "addon.cc",
      "object.cc"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ]
  }]
}