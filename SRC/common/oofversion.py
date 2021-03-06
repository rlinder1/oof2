# -*- python -*-

# This software was produced by NIST, an agency of the U.S. government,
# and by statute is not subject to copyright in the United States.
# Recipients of this software assume all responsibilities associated
# with its operation, modification and maintenance. However, to
# facilitate maintenance we ask that before distributing modified
# versions of this software, you first contact the authors at
# oof_manager@nist.gov. 

## The value assigned to 'version' here is modified by a sed command
## in the make_distutils_dist script when an oof distribution is
## packaged.  The command sed command changes the regular expression
## [0-9]*\.[0-9]*\.[0-9]* to the new version number.  The regular
## expression is intended to match the *old* version number, which it
## will as long as the old version number is of the form
## "digits.digits.digits".

# The make_dist script edits the following line when a distribution is
# built. Don't change it by hand.  On the git master branch,
# "(unreleased)" is replaced by the version number.
version_from_make_dist = "2.1.13-test"

version = version_from_make_dist

# This version tag is presented to the user on the intro page, and is
# also the reply to the "--version" command-line switch.  It might be
# better characterized as a "release version".  See also "version.py",
# which is the version number used when writing and reading data
# files.

